#![no_std]
#![no_main]

use embedded_hal::digital::v2::OutputPin;
use ufmt::uwriteln;
use panic_halt as _;

#[arduino_hal::entry]
fn main() -> ! {
    let dp = arduino_hal::Peripherals::take().unwrap();
    let pins = arduino_hal::pins!(dp);
    let mut serial = arduino_hal::default_serial!(dp, pins, 57600);

    let mut adc = arduino_hal::Adc::new(dp.ADC, Default::default());

    let button = pins.d6.into_pull_up_input();
    let potentiometer0 = pins.a0.into_analog_input(&mut adc);
    let potentiometer1 = pins.a1.into_analog_input(&mut adc);
    let potentiometer2 = pins.a2.into_analog_input(&mut adc);

    let mut green_led = pins.d11.into_output();
    let mut red_led = pins.d12.into_output();
    let mut white_led = pins.d13.into_output();

    loop {
        let pot_value0: u16 = adc.read_blocking(&potentiometer0);
        let pot_value1: u16 = adc.read_blocking(&potentiometer1);
        let pot_value2: u16 = adc.read_blocking(&potentiometer2);
        uwriteln!(&mut serial, "Potentiometer0: {}\r", pot_value0);
        uwriteln!(&mut serial, "Potentiometer1: {}\r", pot_value1);
        uwriteln!(&mut serial, "Potentiometer2: {}\r", pot_value2);

        blinking(&mut green_led, &mut red_led, &mut white_led, 300);
        if button.is_low() {
            blinking(&mut green_led, &mut red_led, &mut white_led, 300);
        } else {
            blinking(&mut green_led, &mut red_led, &mut white_led, 80);
        }
        arduino_hal::delay_ms(600);
    }
}

fn blinking<Pin1, Pin2, Pin3>(
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
    for _ in 0..5 {
        green_led.set_high().ok();
        red_led.set_high().ok();
        white_led.set_high().ok();
        arduino_hal::delay_ms(delay);
        green_led.set_low().ok();
        red_led.set_low().ok();
        white_led.set_low().ok();
        arduino_hal::delay_ms(delay);
    }
}

