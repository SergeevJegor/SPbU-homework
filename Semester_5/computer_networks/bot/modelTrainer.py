from keras.preprocessing.text import text_to_word_sequence
from generator import Generator
from config import Config


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


def train_and_save_model(filename):
    cfg = Config(epochs=80)
    wordlist = load_worlist_file(filename)
    gen = Generator(wordlist=wordlist, config=cfg)

    gen.fit()

    gen.save('my_model', overwrite=True)


if __name__ == '__main__':
    train_and_save_model('model_source.txt')
