"""Render the Week 5 numeric-template UML diagram as a JPG."""

from pathlib import Path
import math

from PIL import Image, ImageDraw, ImageFont


OUTPUT = Path(__file__).parent / "figures" / "week5-template-uml.jpg"
WIDTH, HEIGHT = 2000, 1500


def load_font(size: int, bold: bool = False) -> ImageFont.FreeTypeFont:
    windows_font = Path("C:/Windows/Fonts/arialbd.ttf" if bold else "C:/Windows/Fonts/arial.ttf")
    if windows_font.exists():
        return ImageFont.truetype(str(windows_font), size)
    return ImageFont.truetype("DejaVuSans-Bold.ttf" if bold else "DejaVuSans.ttf", size)


image = Image.new("RGB", (WIDTH, HEIGHT), "#f5f7fb")
draw = ImageDraw.Draw(image)
font = load_font(21)
header_font = load_font(25, bold=True)
title_font = load_font(38, bold=True)

draw.text((70, 35), "Week 5 — Numeric Template Class Layout", font=title_font, fill="#17233b")
draw.text((72, 88), "Public methods (+), private data (−); adapters convert to the existing double-based algorithms.", font=font, fill="#43516b")


def class_box(x, y, width, height, name, attributes, methods):
    draw.rounded_rectangle((x, y, x + width, y + height), radius=12, fill="white", outline="#344b6b", width=3)
    header_height = 52
    draw.rounded_rectangle((x, y, x + width, y + header_height), radius=12, fill="#d9e8fb", outline="#344b6b", width=3)
    draw.rectangle((x, y + header_height - 12, x + width, y + header_height), fill="#d9e8fb")
    draw.text((x + 16, y + 11), name, font=header_font, fill="#12233f")

    line_y = y + header_height + 12
    for item in attributes:
        draw.text((x + 17, line_y), item, font=font, fill="#243249")
        line_y += 31
    draw.line((x, line_y + 4, x + width, line_y + 4), fill="#8a9ab0", width=2)
    line_y += 15
    for item in methods:
        draw.text((x + 17, line_y), item, font=font, fill="#243249")
        line_y += 31


def relation(points, label, label_position, composition=False, dashed=False):
    if dashed:
        for start, end in zip(points, points[1:]):
            x1, y1 = start
            x2, y2 = end
            distance = math.hypot(x2 - x1, y2 - y1)
            steps = max(1, int(distance // 18))
            for index in range(0, steps, 2):
                first = index / steps
                last = min(index + 1, steps) / steps
                draw.line((x1 + (x2 - x1) * first, y1 + (y2 - y1) * first,
                           x1 + (x2 - x1) * last, y1 + (y2 - y1) * last), fill="#8a5da8", width=3)
    else:
        draw.line(points, fill="#187b8f", width=4, joint="curve")

    start_x, start_y = points[0]
    next_x, next_y = points[1]
    end_x, end_y = points[-1]
    prior_x, prior_y = points[-2]
    angle = math.atan2(end_y - prior_y, end_x - prior_x)
    head_length = 18
    left = (end_x + head_length * math.cos(angle + 2.55), end_y + head_length * math.sin(angle + 2.55))
    right = (end_x + head_length * math.cos(angle - 2.55), end_y + head_length * math.sin(angle - 2.55))
    draw.polygon([(end_x, end_y), left, right], fill="#8a5da8" if dashed else "#187b8f")

    if composition:
        source_angle = math.atan2(next_y - start_y, next_x - start_x)
        back = (start_x - 18 * math.cos(source_angle), start_y - 18 * math.sin(source_angle))
        side_x = 9 * math.sin(source_angle)
        side_y = -9 * math.cos(source_angle)
        draw.polygon([(start_x, start_y), (back[0] + side_x, back[1] + side_y),
                      back, (back[0] - side_x, back[1] - side_y)], fill="#187b8f")
    draw.text(label_position, label, font=font, fill="#126376" if not dashed else "#70408f")


class_box(70, 165, 480, 230, "CsvDataProcessor<T>", [], [
    "+ load(path, has_header)", "+ returns NumericDataset<T>"])
class_box(715, 155, 465, 250, "NumericDataset<T>", [
    "+ Matrix<T> features", "+ vector<T> target"], [])
class_box(1400, 155, 500, 325, "Matrix<T>", [
    "− vector<vector<T>> values_"], [
    "+ rows(), columns()", "+ multiply<U>(vector<U>)", "+ transpose(), to_double()"])
class_box(70, 665, 525, 310, "TypedLinearRegression<X, Y>", [
    "− LinearRegression model_"], [
    "+ fit_closed_form(x, y)", "+ fit_gradient_descent(x, y)",
    "+ fit_stochastic_gradient_descent(...)", "+ predict<PredictionT>(x) → double"])
class_box(770, 695, 470, 285, "LinearRegression", [
    "− double intercept_", "− double slope_", "− bool fitted_"], [
    "+ fit_closed_form(x, y)", "+ predict(x) → double"])
class_box(1400, 640, 500, 340, "TypedLassoRegression<F, Y>", [
    "− LassoFit fit_", "− bool fitted_"], [
    "+ fit(Matrix<F>, vector<Y>, lambda)", "+ predict(Matrix<F>)", "+ result()"])
class_box(700, 1110, 500, 280, "LassoFit", [
    "+ vector<double> coefficients", "+ double intercept", "+ double cost"], [
    "+ int passes"])
class_box(1400, 1110, 500, 230, "LASSO core functions", [], [
    "+ coordinate_descent(...)", "+ predict_rows(...)"])

relation([(550, 275), (715, 275)], "creates", (590, 237))
relation([(1180, 280), (1400, 280)], "contains", (1235, 242), composition=True)
relation([(595, 800), (770, 800)], "wraps", (640, 758), composition=True)
relation([(1400, 835), (1300, 835), (1300, 1010), (950, 1010), (950, 1110)],
         "stores result", (1025, 1022), composition=True)
relation([(1650, 980), (1650, 1110)], "calls", (1668, 1030))
relation([(1650, 480), (1650, 640)], "accepts Matrix<F>", (1670, 535), dashed=True)

draw.text((70, 1430), "Composition: filled diamond. Dependency: uses or accepts. X/Y/F are caller-selected numeric types.", font=font, fill="#43516b")
OUTPUT.parent.mkdir(parents=True, exist_ok=True)
image.save(OUTPUT, "JPEG", quality=94, optimize=True)
print(OUTPUT.resolve())
