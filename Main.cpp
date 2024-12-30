// Main.cpp

#include "SVGDocuments.h"  // Đảm bảo bạn có lớp SVGDocuments để xử lý SVG
#include <gdiplus.h>

// Biến toàn cục
float rotationAngle = 30.0f;  // Góc xoay cố định
bool hasRendered = false;     // Cờ để xác định đã render hay chưa
int windowWidth = 800;        // Chiều rộng cửa sổ mặc định
int windowHeight = 600;       // Chiều cao cửa sổ mặc định
std::string FileName = "svg-14.svg";

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
        RECT window;
        GetWindowRect(hwnd, &window);

        // Khởi tạo GDI+ Graphics
        Gdiplus::Graphics graphics(hdc);

        // Xóa màn hình để tránh nhấp nháy
        graphics.Clear(Gdiplus::Color(255, 255, 255));  // Màu nền trắng (RGB)

        // Tính toán scale và rotation
        RotateGraphics(graphics, rotationAngle, windowWidth, windowHeight);
        ScaleGraphics(graphics, 800, 600, windowWidth, windowHeight);
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

int main() {
    try {
        // Khởi tạo GDI+
        Gdiplus::GdiplusStartupInput gdiplusStartupInput;
        ULONG_PTR gdiplusToken;
        GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

        // Định nghĩa lớp cửa sổ
        const wchar_t* className = L"SVGWindowClass";
        WNDCLASSW wc = { 0 };
        wc.lpfnWndProc = WindowProc;
        wc.hInstance = GetModuleHandle(NULL);
        wc.lpszClassName = className;

        // Đăng ký lớp cửa sổ
        if (!RegisterClassW(&wc)) {
            MessageBoxW(NULL, L"Window class registration failed!", L"Error", MB_OK | MB_ICONERROR);
            return 0;
        }

        // Tạo cửa sổ
        HWND hwnd = CreateWindowExW(0, className, L"SVG Renderer", WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
            NULL, NULL, wc.hInstance, NULL);

        if (hwnd == NULL) {
            MessageBoxW(NULL, L"CreateWindowEx failed!", L"Error", MB_OK | MB_ICONERROR);
            return 0;
        }

        // Hiển thị cửa sổ
        ShowWindow(hwnd, SW_SHOWNORMAL);
        UpdateWindow(hwnd);

        // Vòng lặp xử lý sự kiện
        MSG msg;
        while (GetMessage(&msg, NULL, 0, 0)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // Dừng GDI+
        Gdiplus::GdiplusShutdown(gdiplusToken);
    }
    
    catch (const std::exception& ex) {
		std::cerr << "Exception: " << ex.what() << std::endl;
	}

    catch (...) {
        MessageBoxW(NULL, L"An unknown error occurred!", L"Error", MB_OK | MB_ICONERROR);
        return -1;
    }

    return 0;
}
