#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define EXYNOS_LDFW_MAGIC 0x10adab1e

struct fw_header {
	uint32_t magic;
	uint32_t size;
	uint32_t init_entry;
	uint32_t entry_point;
	uint32_t suspend_entry;
	uint32_t resume_entry;
	uint32_t start_smc_id;
	uint32_t version;
	uint32_t set_runtime_entry;
	uint32_t reserved1;
	uint32_t reserved2;
	uint32_t reserved3;
	char fw_name[16];
};

static int extract_ldfws(const char *path)
{
	FILE *fp = fopen(path, "rb");
	if (!fp) {
		perror("Unable to open LDFW file");
		return -1;
	}

	uint64_t offset = 0;
	int index = 0;

	while (1) {
		struct fw_header hdr;

		if (fseek(fp, offset, SEEK_SET) != 0)
		break;

		if (fread(&hdr, sizeof(hdr), 1, fp) != 1)
		break;

		if (hdr.magic != EXYNOS_LDFW_MAGIC)
		break;

		char name[17] = {0};
		strncpy(name, hdr.fw_name, sizeof(hdr.fw_name));

		printf("ldfw [%d]: ldfw version 0x%x name: %s size: 0x%x\n",
			index, hdr.version, name, hdr.size);

		printf("init entry: 0x%x, entrypoint: 0x%x, start_smc_id: 0x%x\n\n",
			hdr.init_entry, hdr.entry_point, hdr.start_smc_id);

		uint8_t *buf = malloc(hdr.size);
		if (!buf) {
			perror("Unable to allocate memory for LDFW extraction");
			fclose(fp);
			return -1;
		}

		fseek(fp, offset, SEEK_SET);
		if (fread(buf, 1, hdr.size, fp) != hdr.size) {
			perror("Unable to read LDFW");
			goto fail;
		}

		char out_name[64];
		snprintf(out_name, sizeof(out_name), "%s.ldfw", name);

		FILE *out = fopen(out_name, "wb");
		if (!out) {
			perror("Unable to open output file for saving");
		}

		fwrite(buf, 1, hdr.size, out);
		fclose(out);
		free(buf);

		offset += hdr.size;
		index++;
		continue;

fail:
		free(buf);
		fclose(fp);
		return -1;
	}

	fclose(fp);
	return 0;
}

int main(int argc, char **argv)
{
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <ldfw_image>\n", argv[0]);
		return 1;
	}

	return extract_ldfws(argv[1]);
}
