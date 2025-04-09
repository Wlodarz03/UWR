use std::fs::File;
use std::io::prelude::*;

#[derive(Clone)]
struct Color{
    red: u8,
    green: u8,
    blue: u8,
}

struct Image{
    height: u32,
    width: u32,
    pixels: Vec<Color>,
}

impl Image{ 

    fn new(width: u32, height: u32) -> Image{
        let pixels = vec![Color { red: 0, green: 0, blue: 0 }; (width * height) as usize];
        Image { height, width, pixels }
    }

    fn set_pixel(&mut self, x: u32, y: u32,color: Color){
        if x < self.width && y < self.height{
            let index = (y * self.width + x) as usize;
            self.pixels[index] = color;
        }
    }

    fn save_ppm(&self, name: &str) -> std::io::Result<()>{
        let mut file = File::create(name)?;
        file.write_all(format!("P3\n{} {}\n255\n", self.width, self.height).as_bytes())?;

        for pixel in &self.pixels {
            file.write_all(format!("{} {} {}\n", pixel.red, pixel.green, pixel.blue).as_bytes())?;
        }

        Ok(())
    }
}

struct Complex{
    real: f64,
    imaginary: f64,
}

impl Complex{
    fn new(real: f64, imaginary: f64) -> Complex {
        Complex {real, imaginary}
    }

    fn add(&self, other: &Complex) -> Complex {
        Complex { 
            real: self.real + other.real,
            imaginary: self.imaginary + other.imaginary,
        }
    }

    fn substract(&self, other: &Complex) -> Complex {
        Complex {
            real: self.real - other.real,
            imaginary: self.imaginary - other.imaginary,
        }
    }

    fn multiply(&self, other: &Complex) -> Complex {
        Complex {
            real: self.real * other.real - self.imaginary * other.imaginary,
            imaginary: self.real * other.imaginary + self.imaginary * other.real,
        }
    }

    fn divide(&self, other: &Complex) -> Complex {
        let a = self.real;
        let b = self.imaginary;
        let c = other.real;
        let d = other.imaginary;
        if c == 0.0 && d == 0.0{
            Complex {
                real: f64::NAN,
                imaginary: f64::NAN,
            }
        }
        else{
            Complex {
                real: (a*c + b*d) / (c*c + d*d),
                imaginary: (b*c - a*d) / (c*c + d*d),
            }
        }
    }
    fn modul(&self) -> f64 {
        (self.real * self.real + self.imaginary * self.imaginary).sqrt()
    }

}

fn mandelbrot(c: Complex, max_iter: u32) -> u32 {
    let mut z = Complex::new(0.0, 0.0);
    let mut n = 0;
    while n < max_iter && z.modul() <= 2.0 {
        z = z.multiply(&z).add(&c);
        n += 1;
    }
    n
}

fn generate_mandelbrot(width: u32, height: u32, max_iter: u32, x_min: f64, x_max: f64, y_min: f64, y_max: f64) -> Image {
    let mut img = Image::new(width, height);

    for y in 0..height {
        for x in 0..width {
            let x_scaled = x as f64 / width as f64 * (x_max - x_min) + x_min;
            let y_scaled = y as f64 / height as f64 * (y_max - y_min) + y_min;

            let c = Complex::new(x_scaled, y_scaled);
            let color_value = mandelbrot(c, max_iter);
            let color = Color {
                red: (color_value % 256) as u8,
                green: 0,
                blue: 0,
            };

            img.set_pixel(x, y, color);
        }
    }
    img
}

fn main(){
    let max_iter = 1000;
    let img1 = generate_mandelbrot(3840, 2160, max_iter, -2.0, 1.0, -1.5, 1.5); //calosc, duza rozdzielczosc
    let img2 = generate_mandelbrot(800, 600, max_iter, -2.0, 1.0, -1.5, 1.5); //calosc, mala rozdzielczosc
    let img3 = generate_mandelbrot(3840, 2160, max_iter, -2.0, -1.0, -0.5, 0.5); //lewy srodek, duza rozdzielczosc
    let img4 = generate_mandelbrot(1920, 1080, max_iter, 0.0, 1.0, 0.25, 1.5); //prawy dol, srednia rozdzielczosc
    let img5 = generate_mandelbrot(1280, 720, max_iter, -1.5, -0.5, -0.25, 0.25); //srodek, mniejsza rozdzielczosc
    let img6 = generate_mandelbrot(800, 700, max_iter, -0.348547, -0.60659, -0.348547, -0.60659);

    // img1.save_ppm("mandelbrot1.ppm");
    // img2.save_ppm("mandelbrot2.ppm");
    // img3.save_ppm("mandelbrot3.ppm");
    // img4.save_ppm("mandelbrot4.ppm");
    // img5.save_ppm("mandelbrot5.ppm");
    // img6.save_ppm("mandlebrot6.ppm");
}