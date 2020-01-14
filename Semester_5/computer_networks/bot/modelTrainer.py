from keras.preprocessing.text import text_to_word_sequence
import sys
import os
sys.path.append(os.path.abspath('./startup-name-generator'))
import sng


def load_worlist_file(filename):
    wordlist_file = open(filename, 'r')
    if wordlist_file:
        content = wordlist_file.read().replace('\n', ' ')
        wordlist = text_to_word_sequence(
            content,
            filters='!"#$%&()*+,-./:;<=>?@[\]^_`{|}~0123456789–…\'\"’«·»'
        )
        return wordlist
    else:
        raise FileNotFoundError('Could not find the file ' + str(wordlist_file))


cfg = sng.Config(epochs=80)
wordlist = load_worlist_file('model_source.txt')
gen = sng.Generator(wordlist=wordlist, config=cfg)

gen.fit()

gen.save('my_model', overwrite=True)
