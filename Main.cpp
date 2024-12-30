// Main.cpp

#include "SVGDocuments.h"  // Đảm bảo bạn có lớp SVGDocuments để xử lý SVG
#include <gdiplus.h>

// Biến toàn cục
float rotationAngle = 30.0f;  // Góc xoay cố định
bool hasRendered = false;     // Cờ để xác định đã render hay chưa
int windowWidth = 800;        // Chiều rộng cửa sổ mặc định
int windowHeight = 600;       // Chiều cao cửa sổ mặc định
<<<<<<< HEAD
std::string FileName = "svg-14.svg";
=======
std::string svgFilePath = "svg-02.svg";  // Default path
>>>>>>> bdff51b2642e4b1bea23852307c0aa3840ef044f

// Hàm thực hiện phép xoay đồ họa
void RotateGraphics(Gdiplus::Graphics& graphics, float angle, int width, int height) {
    float centerX = width / 2;
    float centerY = height / 2;

    // Tạo đối tượng Matrix cho phép xoay
    Gdiplus::Matrix matrix;

    // Xoay quanh điểm trung tâm
    matrix.RotateAt(angle, Gdiplus::PointF(centerX, centerY));

    // Áp dụng phép xoay
    graphics.SetTransform(&matrix);
}

// Hàm scale đồ họa để phù hợp với kích thước cửa sổ
void ScaleGraphics(Gdiplus::Graphics& graphics, int originalWidth, int originalHeight, int newWidth, int newHeight) {
    float scaleX = static_cast<float>(newWidth) / originalWidth;
    float scaleY = static_cast<float>(newHeight) / originalHeight;

    // Áp dụng scale theo tỷ lệ
    graphics.ScaleTransform(scaleX, scaleY);
}

// Hàm xử lý vẽ lên cửa sổ
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static SVGDocuments svg;  // Đối tượng SVGDocuments toàn cục

    switch (uMsg) {
    case WM_PAINT: {
        // Khởi tạo Graphics object
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
<<<<<<< HEAD
        RECT window;
        GetWindowRect(hwnd, &window);
=======
>>>>>>> bdff51b2642e4b1bea23852307c0aa3840ef044f

        // Khởi tạo GDI+ Graphics
        Gdiplus::Graphics graphics(hdc);

        // Xóa màn hình để tránh nhấp nháy
        graphics.Clear(Gdiplus::Color(255, 255, 255));  // Màu nền trắng (RGB)

        // Tính toán scale và rotation
        RotateGraphics(graphics, rotationAngle, windowWidth, windowHeight);
        ScaleGraphics(graphics, 800, 600, windowWidth, windowHeight);
<<<<<<< HEAD
        Viewbox* viewbox = new Viewbox();

        // Tải và render file SVG
        if (!hasRendered) {  // Tải SVG lần đầu
            svg = svg.loadFile(FileName, viewbox);  // Đảm bảo đường dẫn chính xác
            hasRendered = true;
        }

        viewbox->render(graphics, window);

        // Render SVG với các transform áp dụng
        svg.render(graphics);

        delete viewbox;
=======

        // Tải và render file SVG
        if (!hasRendered) {  // Tải SVG lần đầu
            svg = svg.loadFile(svgFilePath);  // Đảm bảo đường dẫn chính xác
            hasRendered = true;
        }

        // Render SVG với các transform áp dụng
        svg.render(hdc);
>>>>>>> bdff51b2642e4b1bea23852307c0aa3840ef044f

        EndPaint(hwnd, &ps);
        return 0;
    }

    case WM_SIZE: {
        // Cập nhật kích thước cửa sổ
        RECT rect;
        GetClientRect(hwnd, &rect);
        windowWidth = rect.right - rect.left;
        windowHeight = rect.bottom - rect.top;

        // Yêu cầu vẽ lại
        InvalidateRect(hwnd, NULL, TRUE);
        return 0;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

<<<<<<< HEAD
int main() {
    try {
        // Khởi tạo GDI+
=======
int main(int argc, char* argv[]) {
    try {
        // Handle command-line argument for SVG file path
        
        if (argc > 1) {
            svgFilePath = argv[1];  // Use the argument passed
        }

        std::cout << "Loading SVG from: " << svgFilePath << std::endl;

        // Initialize GDI+
>>>>>>> bdff51b2642e4b1bea23852307c0aa3840ef044f
        Gdiplus::GdiplusStartupInput gdiplusStartupInput;
        ULONG_PTR gdiplusToken;
        GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

<<<<<<< HEAD
        // Định nghĩa lớp cửa sổ
=======
        // Define window class
>>>>>>> bdff51b2642e4b1bea23852307c0aa3840ef044f
        const wchar_t* className = L"SVGWindowClass";
        WNDCLASSW wc = { 0 };
        wc.lpfnWndProc = WindowProc;
        wc.hInstance = GetModuleHandle(NULL);
        wc.lpszClassName = className;

<<<<<<< HEAD
        // Đăng ký lớp cửa sổ
=======
        // Register window class
>>>>>>> bdff51b2642e4b1bea23852307c0aa3840ef044f
        if (!RegisterClassW(&wc)) {
            MessageBoxW(NULL, L"Window class registration failed!", L"Error", MB_OK | MB_ICONERROR);
            return 0;
        }

<<<<<<< HEAD
        // Tạo cửa sổ
=======
        // Create the window
>>>>>>> bdff51b2642e4b1bea23852307c0aa3840ef044f
        HWND hwnd = CreateWindowExW(0, className, L"SVG Renderer", WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
            NULL, NULL, wc.hInstance, NULL);

        if (hwnd == NULL) {
            MessageBoxW(NULL, L"CreateWindowEx failed!", L"Error", MB_OK | MB_ICONERROR);
            return 0;
        }

<<<<<<< HEAD
        // Hiển thị cửa sổ
        ShowWindow(hwnd, SW_SHOWNORMAL);
        UpdateWindow(hwnd);

        // Vòng lặp xử lý sự kiện
=======
        // Show the window
        ShowWindow(hwnd, SW_SHOWNORMAL);
        UpdateWindow(hwnd);

        // Main event loop
>>>>>>> bdff51b2642e4b1bea23852307c0aa3840ef044f
        MSG msg;
        while (GetMessage(&msg, NULL, 0, 0)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

<<<<<<< HEAD
        // Dừng GDI+
        Gdiplus::GdiplusShutdown(gdiplusToken);
    }
    
    catch (const std::exception& ex) {
		std::cerr << "Exception: " << ex.what() << std::endl;
	}
=======
        // Shutdown GDI+
        Gdiplus::GdiplusShutdown(gdiplusToken);
    }

    catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
    }
>>>>>>> bdff51b2642e4b1bea23852307c0aa3840ef044f

    catch (...) {
        MessageBoxW(NULL, L"An unknown error occurred!", L"Error", MB_OK | MB_ICONERROR);
        return -1;
    }

    return 0;
<<<<<<< HEAD
}
=======
}
>>>>>>> bdff51b2642e4b1bea23852307c0aa3840ef044f
