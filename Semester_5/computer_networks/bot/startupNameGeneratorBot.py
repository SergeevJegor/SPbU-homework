import telebot

# Startup-name-generator files import:
import sys
import os
sys.path.append(os.path.abspath('./startup-name-generator'))
import sng

generator = sng.Generator.load('my_model')

bot = telebot.TeleBot("")

markup = telebot.types.ReplyKeyboardMarkup(resize_keyboard=True)
gen_button = telebot.types.KeyboardButton('Generate')
markup.add(gen_button)


@bot.message_handler(commands=['start'])
def send_welcome(message):
    start_message = 'Hi there!\nPress button \"Generate\" to get a startup name.'
    bot.send_message(message.chat.id, start_message, reply_markup=markup)


@bot.message_handler(commands=['help'])
def send_help(message):
    help_message = 'Press \"Generate\" button to get a startup name.'
    bot.send_message(message.chat.id, help_message)


@bot.message_handler(func=lambda message: message.text == 'Generate')
def answer_message(message):
    bot.send_message(message.chat.id, generator.simulate(1))


bot.polling()
