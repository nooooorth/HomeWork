import docx
import collections
import ctypes


from tkinter.filedialog import *

count = []

top = Tk()
top.geometry("500x600")
top.title("词频统计")

fullText_Frame = Frame(top)
fullList_Frame = Frame(top)
keyWord_Frame = Frame(top)
keyList_Frame = Frame(top)
button_Frame = Frame(top)
query_Frame = Frame(top)
author_Frame = Frame(top)

fullText_Label1 = Label(fullText_Frame)
fullText_Label2 = Label(fullText_Frame)
keyWord_Label1 = Label(keyWord_Frame)
keyWord_Label2 = Label(keyWord_Frame)
queryTip_Label = Label(query_Frame)
queryMessage_Label = Label(query_Frame)
queryResult_Label = Label(query_Frame)
author_Label = Label(author_Frame)

fullText_List = Listbox(fullList_Frame)
keyWord_List = Listbox(keyList_Frame)

fullText_Scroller = Scrollbar(fullList_Frame, bd=500)
keyWord_Scroller = Scrollbar(keyList_Frame, bd=500)

fullText_Button = Button(button_Frame)
keyWord_Button = Button(button_Frame)
query_Button = Button(query_Frame)

word_sel = StringVar()
word_input = Entry(query_Frame)


def ui_init():
    fullText_Frame.config(height=53, width=240, bg="red")
    fullText_Frame.place(x=0, y=0)
    keyWord_Frame.config(height=53, width=240, bg="blue")
    keyWord_Frame.place(x=260, y=0)
    fullList_Frame.config(height=347, width=240, bg="yellow")
    fullList_Frame.place(x=0, y=53)
    keyList_Frame.config(height=347, width=240, bg="yellow")
    keyList_Frame.place(x=260, y=53)
    button_Frame.config(height=80, width=500)
    button_Frame.place(x=0, y=400)
    query_Frame.config(height=100, width=500)
    query_Frame.place(x=0, y=480)
    author_Frame.config(height=20, width=500)
    author_Frame.place(x=0, y=580)

    fullText_Label1.config(text="       所有单词词频             ", font=("Verdana", 15))
    fullText_Label1.place(x=0, y=0)
    fullText_Label2.config(text="单词                      词频          ", font=("Verdana", 12))
    fullText_Label2.place(x=0, y=31)
    keyWord_Label1.config(text="        关键词词频             ", font=("Verdana", 15))
    keyWord_Label1.place(x=0, y=0)
    keyWord_Label2.config(text="单词                       词频          ", font=("Verdana", 12))
    keyWord_Label2.place(x=0, y=31)
    queryTip_Label.config(text='请输入需要查询的单词：', font=("Verdana", 12))
    queryTip_Label.place(x=40, y=20)
    queryMessage_Label.config(text='所查询单词的词频为：', font=("Verdana", 12))
    queryMessage_Label.place(x=310, y=20)
    # author_Label.config(text='作者：刘宜柱 S319060037', font=("Verdana", 10))
    # author_Label.place(x=320, y=0)

    fullText_List.config(yscrollcommand=fullText_Scroller.set, height=20, width=27, font=("Courier New", 10))
    fullText_List.pack(side=LEFT)
    fullText_Scroller.config(command=fullText_List.yview)
    fullText_Scroller.pack(side=RIGHT, fill=Y)
    keyWord_List.config(yscrollcommand=keyWord_Scroller.set, height=20, width=27, font=("Courier New", 10))
    keyWord_List.pack(side=LEFT)
    keyWord_Scroller.config(command=keyWord_List.yview)
    keyWord_Scroller.pack(side=RIGHT, fill=Y)

    fullText_Button.config(text="选择文本文件", font=("Verdana", 15),  command=full_select)
    fullText_Button.place(x=40, y=20)
    keyWord_Button.config(text="选择文本文件", font=("Verdana", 15),  command=key_select)
    keyWord_Button.place(x=300, y=20)
    query_Button.config(text="查询", font=("Verdana", 12), command=word_query)
    query_Button.place(x=225, y=50)

    word_input.place(x=60, y=60)


def file_open(filename):
    pat = '[a-zA-Z0-9]+'
    if os.path.splitext(filename)[1] == ".txt":
        file = open(filename, encoding="gb18030", errors="ignore")
        words = re.findall(pat, str.lower(file.read()))
    elif os.path.splitext(filename)[1] == ".docx":
        doc = docx.Document(filename)
        paras = doc.paragraphs
        words = []
        for p in paras:
            for word in re.findall(pat, str.lower(p.text)):
                words.append(word)
    elif filename == "":
        return 0
    else:
        ctypes.windll.user32.MessageBoxA(0,
                                         u"所选文件不是txt或docx文件，请重新选择".encode(
                                             'gb2312'),
                                         u' 提示'.encode('gb2312'), 0)
    return words


def full_select():
    catalog = os.getcwd()
    filename = askopenfilename(initialdir=catalog)
    words = file_open(filename)
    if words != 0:
        word_count(words)


def key_select():
    catalog = os.getcwd()  # 获取当前目录
    filename = askopenfilename(initialdir=catalog)
    words = file_open(filename)
    if words != 0:
        key_count(words)


def word_count(words):
    global count
    count = []
    count.extend(collections.Counter(words).most_common(len(words) - 1))
    fullText_List.delete(0, fullText_List.size())
    keyWord_List.delete(0, keyWord_List.size())
    for word, index in count:
        item = word + " "*(20-len(word)) + str(index)
        fullText_List.insert(END, item)


def key_count(words):
    keyWord_List.delete(0, keyWord_List.size())
    for key_word in words:
        keyword_count = 0
        for word, index in count:
            if (key_word == word) or (len(key_word) > 2 and key_word[:-1] == word) \
                    or ((key_word+'s') == word) or ((key_word[-3:] == 'ies') and (key_word[:-3]+'y' == word))\
                    or (key_word+'es' == word) or (key_word+'ing' == word) or (key_word[:-1]+'ing' == word) \
                    or (key_word+'d' == word) or (key_word[:-1]+'d' == word) or (key_word+'ed' == word):
                keyword_count += index
        item = key_word + " " * (20 - len(key_word)) + str(keyword_count)
        keyWord_List.insert(END, item)


def word_query():
    exist = -1
    word_sel = word_input.get()
    for word, index in count:
        if word == str.lower(word_sel):
            queryResult_Label.config(text=str(index), font=("Verdana", 12))
            queryResult_Label.place(x=360, y=50)
            exist = 1
    if exist == -1:
        queryResult_Label.config(text="单词不存在，请重新输入", font=("Verdana", 12))
        queryResult_Label.place(x=310, y=50)

ui_init()
top.mainloop()
