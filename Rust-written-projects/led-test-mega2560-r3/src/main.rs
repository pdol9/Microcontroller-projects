#![no_std]
#![no_main]

use embedded_hal::digital::v2::{OutputPin, InputPin};
use ufmt::uwriteln;
use panic_halt as _;

#[arduino_hal::entry]
fn main() -> ! {
    let dp = arduino_hal::Peripherals::take().unwrap();
    let pins = arduino_hal::pins!(dp);
    let mut serial = arduino_hal::default_serial!(dp, pins, 57600);

    let button = pins.d6.into_pull_up_input();

    // Rotary encoder pins configuration
    let encoder_a = pins.d2.into_floating_input();
    let encoder_b = pins.d3.into_floating_input();

    let mut encoder = Encoder::new(encoder_a, encoder_b);

    let mut led_delay = 500;

    let mut green_led = pins.d11.into_output();
    let mut red_led = pins.d12.into_output();
    let mut white_led = pins.d13.into_output();

    loop {
        encoder.update();
        let position = encoder.get_position();

        led_delay = (500 + position * 50).max(0) as u16;
        // WIP
        //let a_state = encoder_a.is_high().unwrap_or(false);
        //let b_state = encoder_b.is_high().unwrap_or(false);

        //uwriteln!(&mut serial, "Encoder A: {}, Encoder B: {}\r", a_state as u8, b_state as u8).unwrap();
        uwriteln!(&mut serial, "Encoder Position: {}\r", position).unwrap();
        uwriteln!(&mut serial, "Current Delay: {}\r", led_delay).unwrap();

        arduino_hal::delay_ms(led_delay);

        initial_blinking(&mut green_led, &mut red_led, &mut white_led, 1000);
        if button.is_high() {
          blinking(&mut green_led, &mut red_led, &mut white_led, 300, 5);
          arduino_hal::delay_ms(1500);
          uwriteln!(&mut serial, " IS HIGH -- Push_button: {}\r", true).unwrap();
        } else {
          blinking(&mut green_led, &mut red_led, &mut white_led, 50, 10);
          uwriteln!(&mut serial, " IS LOW -- Push_button: {}\r", false).unwrap();
        }
    }
}

fn blinking<Pin1, Pin2, Pin3>(
    green_led: &mut Pin1,
    red_led: &mut Pin2,
    white_led: &mut Pin3,
    delay: u16,
    repetitions: u16,
)
where
    Pin1: OutputPin,
    Pin2: OutputPin,
    Pin3: OutputPin,
{
    for _ in 0..repetitions {
        green_led.set_high().ok();
        arduino_hal::delay_ms(delay);
        red_led.set_high().ok();
        green_led.set_low().ok();
        arduino_hal::delay_ms(delay);
        white_led.set_high().ok();
        red_led.set_low().ok();
        arduino_hal::delay_ms(delay);
        white_led.set_low().ok();
    }
}

fn initial_blinking<Pin1, Pin2, Pin3>(
    green_led: &mut Pin1,
    red_led: &mut Pin2,
    white_led: &mut Pin3,
    delay: u16,
)
where
    Pin1: OutputPin,
    Pin2: OutputPin,
    Pin3: OutputPin,
{
        green_led.set_high().ok();
        arduino_hal::delay_ms(delay);
        red_led.set_high().ok();
        green_led.set_low().ok();
        arduino_hal::delay_ms(delay);
        white_led.set_high().ok();
        red_led.set_low().ok();
        arduino_hal::delay_ms(delay);
        white_led.set_low().ok();
}

struct Encoder<A, B>
where
    A: InputPin,
    B: InputPin,
{
    a_pin: A,
    b_pin: B,
    last_state: bool,
    position: i32,
}

impl<A, B> Encoder<A, B>
where
    A: InputPin,
    B: InputPin,
{
    fn new(a_pin: A, b_pin: B) -> Self {
        let a_state = a_pin.is_high().ok().unwrap_or(false); // Handle potential error
        Self {
            a_pin,
            b_pin,
            last_state: a_state,
            position: 0,
        }
    }

    fn update(&mut self) {
        let a_state = self.a_pin.is_high().ok().unwrap_or(false);
        let b_state = self.b_pin.is_high().ok().unwrap_or(false);
        if a_state != self.last_state {
            if b_state != a_state {
                self.position += 1;
            } else {
                self.position -= 1;
            }
            self.last_state = a_state;
        }
    }

    fn get_position(&self) -> i32 {
        self.position
    }

}
