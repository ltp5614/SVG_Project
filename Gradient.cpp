#include "Gradient.h"


LinearGradient::LinearGradient(std::string x1, std::string y1, std::string x2, std::string y2)
	: x1(x1), y1(y1), x2(x2), y2(y2) {}

RadialGradient::RadialGradient(std::string x1, std::string y1, std::string radius)
	: x1(x1), y1(y1), radius(radius) {}


void LinearGradient::applyForBrush(const Gdiplus::Matrix& matrix, Gdiplus::Brush*& brush, float boundingBoxWidth, float boundingBoxHeight) const
{
	// Hàm nội bộ để chuyển đổi giá trị phần trăm
	auto parsePercentage = [](const std::string& value, float totalSize) -> float {
		if (value.back() == '%') {
			return (std::stof(value.substr(0, value.size() - 1)) / 100.0f) * totalSize;
		}
		return std::stof(value);
		};

	// Chuyển đổi tọa độ gradient
	float x1Real = parsePercentage(x1, boundingBoxWidth);
	float y1Real = parsePercentage(y1, boundingBoxHeight);
	float x2Real = parsePercentage(x2, boundingBoxWidth);
	float y2Real = parsePercentage(y2, boundingBoxHeight);

	Gdiplus::PointF startPoint(x1Real, y1Real);
	Gdiplus::PointF endPoint(x2Real, y2Real);

	// Kiểm tra gradient stops
	if (stops.empty()) {
		std::cerr << "Error: No gradient stops defined." << std::endl;
		brush = nullptr;
		return;
	}

	// Lưu trữ màu sắc và vị trí
	std::vector<Gdiplus::Color> colors;
	std::vector<float> positions;

	for (const auto& stop : stops) {
		ColorSVG parsedColor = ColorSVG::parseColor(stop.color);

		Gdiplus::Color color(
			static_cast<BYTE>(255 * stop.opacity),
			parsedColor.getRed(),
			parsedColor.getGreen(),
			parsedColor.getBlue()
		);

		colors.push_back(color);
		positions.push_back(std::clamp(stop.offset, 0.0f, 1.0f));

		// Tạo LinearGradientBrush
		brush = new Gdiplus::LinearGradientBrush(startPoint, endPoint, colors.front(), colors.back());
		auto linearBrush = static_cast<Gdiplus::LinearGradientBrush*>(brush);

		if (colors.size() != positions.size()) {
			std::cerr << "Error: Mismatched number of colors and positions." << std::endl;
		}

		for (const auto& pos : positions) {
			if (pos < 0.0f || pos > 1.0f) {
				std::cerr << "Error: Position value out of range." << std::endl;
				return;
			}
		}
		for (auto& color : colors) {
			if (color.GetRed() > 255 || color.GetGreen() > 255 || color.GetBlue() > 255) {
				std::cerr << "Error: Color component out of range." << std::endl;
				return;
			}
		}


		for (const auto& stop : stops) {
			if (stop.opacity < 0.0f || stop.opacity > 1.0f) {
				std::cerr << "Error: Opacity value out of range." << std::endl;
				return;
			}
		}


		if (linearBrush) {
			// Áp dụng các gradient stops
			if (linearBrush->SetInterpolationColors(colors.data(), positions.data(), static_cast<INT>(positions.size())) != Gdiplus::Ok) {
				Gdiplus::Status status = linearBrush->GetLastStatus();  // Lấy trạng thái lỗi
				std::cerr << "Error: Failed to apply gradient stops. Error code: " << status << std::endl;
			}

			// Sử dụng WrapModeClamp để gradient không lặp lại
			linearBrush->SetWrapMode(Gdiplus::WrapModeClamp);

			// Áp dụng phép biến đổi
			//linearBrush->SetTransform(&matrix);
		}
		else {
			std::cerr << "Error: Failed to create LinearGradientBrush." << std::endl;
			delete brush;
			brush = nullptr;
		}
	}
}


	void RadialGradient::applyForBrush(const Gdiplus::Matrix & matrix, Gdiplus::Brush * &brush, float boundingBoxWidth, float boundingBoxHeight) const {
		// Tạo RadialGradientBrush
		auto parsePercentage = [](const std::string& value, float size) -> float {
			if (value.back() == '%') {
				return std::stof(value.substr(0, value.size() - 1)) / 100.0f * size;
			}
			return std::stof(value);
			};

		float centerX = parsePercentage(x1, boundingBoxWidth);
		float centerY = parsePercentage(y1, boundingBoxHeight);
		float radiusReal = parsePercentage(radius, min(boundingBoxWidth, boundingBoxHeight));

		Gdiplus::PointF center = Gdiplus::PointF(centerX, centerY);

		std::vector<Gdiplus::Color> colors;
		std::vector<float> positions;

		// Tạo các điểm dừng gradient
		for (const auto& stop : stops) {
			ColorSVG ColorGra = ColorSVG::parseColor(stop.color);
			colors.push_back(Gdiplus::Color(static_cast<BYTE>(255 * stop.opacity), ColorGra.getRed(), ColorGra.getBlue(), ColorGra.getGreen()));
			positions.push_back(stop.offset);
		}

		if (colors.empty()) return;
		Gdiplus::GraphicsPath path;
		path.AddEllipse(0, 0, 1, 1);  // Thêm một hình tròn nhỏ vào đường dẫn

		// Tạo PathGradientBrush từ GraphicsPath
		brush = new Gdiplus::PathGradientBrush(&path);
		auto radialBrush = static_cast<Gdiplus::PathGradientBrush*>(brush);

		// Cài đặt các tham số cho radial gradient
		radialBrush->SetCenterPoint(center); // Điểm trung tâm của gradient
		radialBrush->SetCenterColor(colors[0]); // Màu tại trung tâm
		if (colors.size() > 1) {
			INT count = static_cast<INT>(colors.size()) - 1;
			radialBrush->SetSurroundColors(&colors[1], &count);
		}

		// Cài đặt bán kính (scaling) cho sự chuyển màu của gradient
		radialBrush->SetFocusScales(radiusReal, radiusReal);

		// Áp dụng ma trận biến đổi nếu cần
		radialBrush->SetTransform(&matrix);  // Áp dụng ma trận biến đổi

		std::cout << "Radial gradient applied successfully.\n";
	}

	void RadialGradient::addStop(float offset, const std::string & color, float opacity)
	{
		// Kiểm tra giá trị offset trong phạm vi hợp lệ
		if (offset < 0.0f || offset > 1.0f) {
			std::cout << offset;
			throw std::out_of_range("Offset must be between 0.0 and 1.0");
		}

		// Kiểm tra giá trị opacity trong phạm vi hợp lệ
		if (opacity < 0.0f || opacity > 1.0f) {
			throw std::out_of_range("Opacity must be between 0.0 and 1.0");
		}

		// Tạo GradientStop mới và thêm vào danh sách stops
		GradientStop stop = { offset, color, opacity };
		stops.push_back(stop);

		// Sắp xếp danh sách stops theo thứ tự offset tăng dần (nếu cần)
		std::sort(stops.begin(), stops.end(), [](const GradientStop& a, const GradientStop& b) {
			return a.offset < b.offset;
			});
	}

	void LinearGradient::addStop(float offset, const std::string & color, float opacity)
	{
		// Kiểm tra giá trị offset trong phạm vi hợp lệ
		if (offset < 0.0f || offset > 1.0f) {
			std::cout << offset;
			throw std::out_of_range("Offset must be between 0.0 and 1.0");
		}

		// Kiểm tra giá trị opacity trong phạm vi hợp lệ
		if (opacity < 0.0f || opacity > 1.0f) {
			throw std::out_of_range("Opacity must be between 0.0 and 1.0");
		}

		// Tạo GradientStop mới và thêm vào danh sách stops
		GradientStop stop = { offset, color, opacity };
		stops.push_back(stop);

		// Sắp xếp danh sách stops theo thứ tự offset tăng dần (nếu cần)
		std::sort(stops.begin(), stops.end(), [](const GradientStop& a, const GradientStop& b) {
			return a.offset < b.offset;
			});
	}


	std::vector<GradientStop> Gradient::getStops()
	{
		return stops;
	}
