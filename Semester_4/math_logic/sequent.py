import re
import sys
import pydot


def format_formula(s):
    res = re.sub('([()\][])(\d+ )', '\\1', s)
    res = res.replace(',', ',,')
    right = re.findall(',\(([^,]+)\),', res)
    left = re.findall(',\[([^,]+)],', res)
    res = ', '.join(left) + '\n⊢\n' + ', '.join(right)
    return res


def read_input():
    if len(sys.argv) == 2:
        f = open(sys.argv[1], 'r')
    else:
        f = open('test', 'r')
    return ';,' + f.readline().strip() + ',;'


def brackets_number(s):
    n = 0
    i = 0
    res = s
    while i < len(res):
        if res[i] in '([':
            n += 1
            res = res[:i + 1] + str(n) + ' ' + res[i + 1:]
        elif res[i] in ')]':
            res = res[:i + 1] + str(n) + ' ' + res[i + 1:]
            n -= 1
        i += 1
        assert n >= 0, 'Unbalanced bracket'
    assert not n, 'Unbalanced brackets'
    return res


def match_resolve(match):
    start, bracket, arg1, op, arg2, end = match.group(1, 2, 5, 6, 8, 9)
    re.sub(' ', '', op)
    assert op in ['-', '&', '|', '->']
    rule = bracket + op
    op_map = {'(-': '{}[1 {}]1 {}'.format(start, arg2, end),
              '[-': '{}(1 {})1 {}'.format(start, arg2, end),
              '(&': '{}(1 {})1 {};{}(1 {})1 {}'.format(start, arg1, end, start, arg2, end),
              '[&': '{}[1 {}]1 ,[1 {}]1 {}'.format(start, arg1, arg2, end),
              '(|': '{}(1 {})1 ,(1 {})1 {}'.format(start, arg1, arg2, end),
              '[|': '{}[1 {}]1 {};{}[1 {}]1 {}'.format(start, arg1, end, start, arg2, end),
              '(->': '{}[1 {}]1 ,(1 {})1 {}'.format(start, arg1, arg2, end),
              '[->': '{}(1 {})1 {};{}[1 {}]1 {}'.format(start, arg1, end, start, arg2, end)}
    res = op_map[rule]
    for x in res.split(';'):
        if x:
            graph.add_edge(pydot.Edge(format_formula(match.group(0)), format_formula(x)))
    return res


def check_duplicates(sequent):
    left = re.findall('\[1 ([^])]+)]1 ', sequent)
    right = re.findall('\(1 ([^])]+)\)1 ', sequent)
    # Check for duplicates:
    left = set(left)
    right = set(right)
    if not (left & right):
        p = ''.join([x + '=1\n' for x in left])
        p += ''.join([x + '=0\n' for x in right])
        return p
    return None


if __name__ == '__main__':
    op_regexp = re.compile('([^;]*)([([])1 (\((\d+ )([^,;]+)\)\\4 )?(-|&|->|\|) \((\d+ )([^,;]+)\)\\7[])]1 ([^;]*)')
    s = brackets_number(read_input())
    graph = pydot.Dot(graph_type='digraph')
    graph.set_node_defaults(color='lightgray', shape='ellipse', fontname='Courier', fontsize='10')
    prev = ''
    while s != prev:
        prev = s
        s = re.sub(op_regexp, match_resolve, s)
    counterex = None
    for seq in s.split(';'):
        if seq:
            counterex = check_duplicates(seq)
            if counterex is not None:
                break
    if counterex is None:
        print("Tautology")
    else:
        print('Counterexample:\n' + counterex)
    graph.write('seq_graph.svg', format='svg')
