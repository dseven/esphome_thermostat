float _c_to_f(float c) {
    return((c*9.0/5.0) + 32.0);
}

float _f_to_c(float f) {
    return((f-32.0) * 5.0/9.0);
}

float _new_temp(float old_c, float delta) {
    return _f_to_c(_c_to_f(old_c) + delta);
}

void _increment_target(thermostat::ThermostatClimate *ob, float delta) {
    auto call = ob->make_call();
    if (ob->mode == CLIMATE_MODE_HEAT) {
        call.set_target_temperature_low(_new_temp(ob->target_temperature_low, delta));
    } else if (ob->mode == CLIMATE_MODE_COOL) {
        call.set_target_temperature_high(_new_temp(ob->target_temperature_high, delta));
    }
    call.perform();
}

void _cycle_mode(thermostat::ThermostatClimate *ob) {
    auto call = ob->make_call();
    if (ob->mode == CLIMATE_MODE_OFF) {
        call.set_mode(CLIMATE_MODE_HEAT);
    } else if (ob->mode == CLIMATE_MODE_HEAT) {
        call.set_mode(CLIMATE_MODE_COOL);
    } else if (ob->mode == CLIMATE_MODE_COOL) {
        call.set_mode(CLIMATE_MODE_AUTO);
    } else {
        call.set_mode(CLIMATE_MODE_OFF);
    }
    call.perform();
}

