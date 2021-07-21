## UIPack 



x11 widgets in c.


* UIApplication
* UIWindow
* UIFont
* UILabel
* UIText
* UIImage
* UIKeyboardInput
* UILayout


void UIInitialize (void) __attribute__ ((constructor(102) ));

// setLayout(new FlowLayout(FlowLayout.CENTER, 10, 10));
// add(new Label("Hi There!"));
// add(new Label("Another Label"));

var win = UIWindowCreate(app, "BadaBing", (UIRect){ 100, 100, 400, 300});
var lm = UILayoutManagerCreate(kUILayoutGrid);

UIWindowSetLayoutManager(win, lm);
UIWindowSetRunLoop(win, RunLoop);

var label = UILabelCreate("Hello World", NK_TEXT_LEFT);

UIWindowAdd(win, label);

UIWindowRun(win, NK_WINDOW_NO_SCROLLBAR);

