# Exynos LDFW Extractor

Extracts individual LDFWs (LoaDable FirmWare) from an LDFW iamge

## Compilation

Nothing fancy, just do

```gcc ldfw-extractor.c -o LDFWExtractor```

## Usage

```./LDFWExtractor <ldfw_image>```

## Example Output

```
❯ ./LDFWExtractor ldfw.img 
ldfw [0]: ldfw version 0x50191220 name: CryptoManagerV50 size: 0x211000
init entry: 0x1198, entrypoint: 0x1180, start_smc_id: 0x82001000
ldfw loaded to: 0xbf700000 [1]

ldfw [1]: ldfw version 0x20190710 name: fmp_fw_V20 size: 0x17000
init entry: 0x11c8, entrypoint: 0x11b0, start_smc_id: 0x82001800
ldfw loaded to: 0xbf932000 [1]

ldfw [2]: ldfw version 0x20200110 name: drm_fw size: 0x151000
init entry: 0x1198, entrypoint: 0x1180, start_smc_id: 0x82002000
ldfw loaded to: 0xbf96a000 [1]

ldfw [3]: ldfw version 0x24190710 name: srpmb_fw size: 0x51000
init entry: 0x1198, entrypoint: 0x1180, start_smc_id: 0x82003800
ldfw loaded to: 0xbfadc000 [1]

ldfw [4]: ldfw version 0x20190717 name: hdcp_fw size: 0x21000
init entry: 0x1198, entrypoint: 0x1180, start_smc_id: 0x82004000
ldfw loaded to: 0xbfb4e000 [1]

ldfw [5]: ldfw version 0x20150828 name: tail_fw size: 0x1000
init entry: 0x1000, entrypoint: 0x1070, start_smc_id: 0x82001800
ldfw loaded to: 0xbfb90000 [1]

[1]: ldfw load addresses were based off of calculations done in exynos9830 EL3_MON.
```

## Credits

- @exynos990-mainline ```Portion of the LDFW loading code was taken from lk3rd```
