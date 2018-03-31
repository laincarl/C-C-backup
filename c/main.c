QTextCodec *codec = QTextCodec::codecForName("GB18030");
setWindowTitle(codec->toUnicode("我是中文"));
