

int initialize() {
    if ((rtn = gpioSetup()) != OK)
    {
        dbgPrint(DBG_INFO, "GPIO setup failed :(\n");
        return 1;
    }

    else if (gpioI2cSetup() != OK)
    {
        dbgPrint(DBG_INFO, "i2C setup failed :(\n");
        return 1;
    }
}