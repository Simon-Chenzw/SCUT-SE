// windows macro
#ifdef _WIN32
#define IN_WINDOWS
#endif

// linux macro
#ifdef __linux__
#define IN_LINUX
#endif

#ifdef linux
#define IN_LINUX
#endif

// determine wrong
#if defined(IN_LINUX) && defined(IN_WINDOWS)
#error Detected on two different platforms
#endif

// platform determine end

void terminal_init();

void terminal_uninit();

void clean_keyboard_buffer();

// -1代表没输入
int keyboard_input();

void get_screen_size(int& row, int& col);

// origin row = 1 col = 1
void set_cursor_position(int row, int col);