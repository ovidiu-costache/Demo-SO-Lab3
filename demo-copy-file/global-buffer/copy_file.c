// SPDX-License-Identifier: BSD-3-Clause

#include <stdio.h>
#include <stdlib.h>

// Q: In ce zona de memorie se afla BUFFER_SIZE? De ce?
#define BUFFER_SIZE (1 * 1024 * 1024)  /* 1 MiB */

/*
 * TODO 1: declare the copy buffer the loop in main() reads into and writes
 * from: `buffer`, BUFFER_SIZE bytes, here at file scope.
 *
 * A global like this is laid out by the compiler and exists from before
 * main() runs until the process exits. Nobody allocates it and nobody
 * releases it. After building, `size copy_file` shows where it went.
 */

// Q: Din ce zona de memorie face parte `buffer`? De ce?
char buffer[BUFFER_SIZE];

int main(int argc, char *argv[])
{
	const char *src_path;
	const char *dst_path;
	size_t bytes_read;
	FILE *src;
	FILE *dst;

	if (argc != 3) {
		fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	src_path = argv[1];
	dst_path = argv[2];

	/* Open source file for reading. */
	src = fopen(src_path, "rb");
	if (!src) {
		perror("fopen source");

		// Q: Ce resurse avem de inchis daca deschiderea sursei a esuat?
		goto fail;
	}

	/* Open destination file for writing (create/truncate). */
	dst = fopen(dst_path, "wb");
	if (!dst) {
		perror("fopen destination");

		// Q: De ce mergem la fail_src si nu la fail_dst?
		// Q: Ce face goto?
		goto fail_src;
	}

	/* Read a block from the source into the buffer, write it out, repeat. */
	while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, src)) > 0) {
		/*
		 * TODO 2: write the `bytes_read` bytes now in `buffer` to `dst`.
		 * fwrite() may write fewer than asked (a full disk, for one);
		 * treat that as an error, and leave through the label that
		 * undoes what is open at this point.
		 */
		size_t bytes_written = fwrite(buffer, 1, bytes_read, dst);

		if (bytes_written != bytes_read) {
			fprintf(stderr,
				"fwrite: s-au citit %lu octeti, s-au scris %lu\n",
				bytes_read, bytes_written);

			// Q: Ce fisiere sunt deschise in acest punct?
			goto fail_dst;
		}
	}

	if (ferror(src)) {
		perror("fread");
		goto fail_dst;
	}

	fclose(dst);
	fclose(src);

	/* Nothing to release: the buffer lives until the process exits. */

	printf("Copied '%s' -> '%s'\n", src_path, dst_path);

	return 0;

/*
 * Cleanup pe erori, in ordinea inversa obtinerii resurselor.
 * Executia continua de la o eticheta la urmatoarea.
 */
fail_dst:
	fclose(dst);
fail_src:
	fclose(src);
fail:
	return -1;
}