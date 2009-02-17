#include "crc/crc.h"
#include "crc/crc.c"
#include "tap/tap.h"
#include <string.h>

/* Expected CRCs of 4 of each char. */
static uint32_t crcc_expect[] = {
	0x00000000, 0x99cd23b2, 0x36763195, 0xafbb1227, 0x6cec632a, 0xf5214098, 
	0x5a9a52bf, 0xc357710d, 0xd9d8c654, 0x4015e5e6, 0xefaef7c1, 0x7663d473, 
	0xb534a57e, 0x2cf986cc, 0x834294eb, 0x1a8fb759, 0xb65dfa59, 0x2f90d9eb, 
	0x802bcbcc, 0x19e6e87e, 0xdab19973, 0x437cbac1, 0xecc7a8e6, 0x750a8b54, 
	0x6f853c0d, 0xf6481fbf, 0x59f30d98, 0xc03e2e2a, 0x03695f27, 0x9aa47c95, 
	0x351f6eb2, 0xacd24d00, 0x69578243, 0xf09aa1f1, 0x5f21b3d6, 0xc6ec9064, 
	0x05bbe169, 0x9c76c2db, 0x33cdd0fc, 0xaa00f34e, 0xb08f4417, 0x294267a5, 
	0x86f97582, 0x1f345630, 0xdc63273d, 0x45ae048f, 0xea1516a8, 0x73d8351a, 
	0xdf0a781a, 0x46c75ba8, 0xe97c498f, 0x70b16a3d, 0xb3e61b30, 0x2a2b3882, 
	0x85902aa5, 0x1c5d0917, 0x06d2be4e, 0x9f1f9dfc, 0x30a48fdb, 0xa969ac69, 
	0x6a3edd64, 0xf3f3fed6, 0x5c48ecf1, 0xc585cf43, 0xd2af0486, 0x4b622734, 
	0xe4d93513, 0x7d1416a1, 0xbe4367ac, 0x278e441e, 0x88355639, 0x11f8758b, 
	0x0b77c2d2, 0x92bae160, 0x3d01f347, 0xa4ccd0f5, 0x679ba1f8, 0xfe56824a, 
	0x51ed906d, 0xc820b3df, 0x64f2fedf, 0xfd3fdd6d, 0x5284cf4a, 0xcb49ecf8, 
	0x081e9df5, 0x91d3be47, 0x3e68ac60, 0xa7a58fd2, 0xbd2a388b, 0x24e71b39, 
	0x8b5c091e, 0x12912aac, 0xd1c65ba1, 0x480b7813, 0xe7b06a34, 0x7e7d4986, 
	0xbbf886c5, 0x2235a577, 0x8d8eb750, 0x144394e2, 0xd714e5ef, 0x4ed9c65d, 
	0xe162d47a, 0x78aff7c8, 0x62204091, 0xfbed6323, 0x54567104, 0xcd9b52b6, 
	0x0ecc23bb, 0x97010009, 0x38ba122e, 0xa177319c, 0x0da57c9c, 0x94685f2e, 
	0x3bd34d09, 0xa21e6ebb, 0x61491fb6, 0xf8843c04, 0x573f2e23, 0xcef20d91, 
	0xd47dbac8, 0x4db0997a, 0xe20b8b5d, 0x7bc6a8ef, 0xb891d9e2, 0x215cfa50, 
	0x8ee7e877, 0x172acbc5, 0xa0b27ffd, 0x397f5c4f, 0x96c44e68, 0x0f096dda, 
	0xcc5e1cd7, 0x55933f65, 0xfa282d42, 0x63e50ef0, 0x796ab9a9, 0xe0a79a1b, 
	0x4f1c883c, 0xd6d1ab8e, 0x1586da83, 0x8c4bf931, 0x23f0eb16, 0xba3dc8a4, 
	0x16ef85a4, 0x8f22a616, 0x2099b431, 0xb9549783, 0x7a03e68e, 0xe3cec53c, 
	0x4c75d71b, 0xd5b8f4a9, 0xcf3743f0, 0x56fa6042, 0xf9417265, 0x608c51d7, 
	0xa3db20da, 0x3a160368, 0x95ad114f, 0x0c6032fd, 0xc9e5fdbe, 0x5028de0c, 
	0xff93cc2b, 0x665eef99, 0xa5099e94, 0x3cc4bd26, 0x937faf01, 0x0ab28cb3, 
	0x103d3bea, 0x89f01858, 0x264b0a7f, 0xbf8629cd, 0x7cd158c0, 0xe51c7b72, 
	0x4aa76955, 0xd36a4ae7, 0x7fb807e7, 0xe6752455, 0x49ce3672, 0xd00315c0, 
	0x135464cd, 0x8a99477f, 0x25225558, 0xbcef76ea, 0xa660c1b3, 0x3fade201, 
	0x9016f026, 0x09dbd394, 0xca8ca299, 0x5341812b, 0xfcfa930c, 0x6537b0be, 
	0x721d7b7b, 0xebd058c9, 0x446b4aee, 0xdda6695c, 0x1ef11851, 0x873c3be3, 
	0x288729c4, 0xb14a0a76, 0xabc5bd2f, 0x32089e9d, 0x9db38cba, 0x047eaf08, 
	0xc729de05, 0x5ee4fdb7, 0xf15fef90, 0x6892cc22, 0xc4408122, 0x5d8da290, 
	0xf236b0b7, 0x6bfb9305, 0xa8ace208, 0x3161c1ba, 0x9edad39d, 0x0717f02f, 
	0x1d984776, 0x845564c4, 0x2bee76e3, 0xb2235551, 0x7174245c, 0xe8b907ee, 
	0x470215c9, 0xdecf367b, 0x1b4af938, 0x8287da8a, 0x2d3cc8ad, 0xb4f1eb1f, 
	0x77a69a12, 0xee6bb9a0, 0x41d0ab87, 0xd81d8835, 0xc2923f6c, 0x5b5f1cde, 
	0xf4e40ef9, 0x6d292d4b, 0xae7e5c46, 0x37b37ff4, 0x98086dd3, 0x01c54e61, 
	0xad170361, 0x34da20d3, 0x9b6132f4, 0x02ac1146, 0xc1fb604b, 0x583643f9, 
	0xf78d51de, 0x6e40726c, 0x74cfc535, 0xed02e687, 0x42b9f4a0, 0xdb74d712, 
	0x1823a61f, 0x81ee85ad, 0x2e55978a, 0xb798b438
};

static uint32_t crcc_zero_expect[] = {
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

static uint32_t crc_ieee_expect[] = {
	0x2144df1c, 0xf626d399, 0x54f1c057, 0x8393ccd2, 0xca2ee18a, 0x1d4ced0f,
	0xbf9bfec1, 0x68f9f244, 0x2ce1a471, 0xfb83a8f4, 0x5954bb3a, 0x8e36b7bf,
	0xc78b9ae7, 0x10e99662, 0xb23e85ac, 0x655c8929, 0x3a0e29c6, 0xed6c2543,
	0x4fbb368d, 0x98d93a08, 0xd1641750, 0x06061bd5, 0xa4d1081b, 0x73b3049e,
	0x37ab52ab, 0xe0c95e2e, 0x421e4de0, 0x957c4165, 0xdcc16c3d, 0x0ba360b8,
	0xa9747376, 0x7e167ff3, 0x17d132a8, 0xc0b33e2d, 0x62642de3, 0xb5062166,
	0xfcbb0c3e, 0x2bd900bb, 0x890e1375, 0x5e6c1ff0, 0x1a7449c5, 0xcd164540,
	0x6fc1568e, 0xb8a35a0b, 0xf11e7753, 0x267c7bd6, 0x84ab6818, 0x53c9649d,
	0x0c9bc472, 0xdbf9c8f7, 0x792edb39, 0xae4cd7bc, 0xe7f1fae4, 0x3093f661,
	0x9244e5af, 0x4526e92a, 0x013ebf1f, 0xd65cb39a, 0x748ba054, 0xa3e9acd1,
	0xea548189, 0x3d368d0c, 0x9fe19ec2, 0x48839247, 0x4c6f0474, 0x9b0d08f1,
	0x39da1b3f, 0xeeb817ba, 0xa7053ae2, 0x70673667, 0xd2b025a9, 0x05d2292c,
	0x41ca7f19, 0x96a8739c, 0x347f6052, 0xe31d6cd7, 0xaaa0418f, 0x7dc24d0a,
	0xdf155ec4, 0x08775241, 0x5725f2ae, 0x8047fe2b, 0x2290ede5, 0xf5f2e160,
	0xbc4fcc38, 0x6b2dc0bd, 0xc9fad373, 0x1e98dff6, 0x5a8089c3, 0x8de28546,
	0x2f359688, 0xf8579a0d, 0xb1eab755, 0x6688bbd0, 0xc45fa81e, 0x133da49b,
	0x7afae9c0, 0xad98e545, 0x0f4ff68b, 0xd82dfa0e, 0x9190d756, 0x46f2dbd3,
	0xe425c81d, 0x3347c498, 0x775f92ad, 0xa03d9e28, 0x02ea8de6, 0xd5888163,
	0x9c35ac3b, 0x4b57a0be, 0xe980b370, 0x3ee2bff5, 0x61b01f1a, 0xb6d2139f,
	0x14050051, 0xc3670cd4, 0x8ada218c, 0x5db82d09, 0xff6f3ec7, 0x280d3242,
	0x6c156477, 0xbb7768f2, 0x19a07b3c, 0xcec277b9, 0x877f5ae1, 0x501d5664,
	0xf2ca45aa, 0x25a8492f, 0xfb1369cc, 0x2c716549, 0x8ea67687, 0x59c47a02,
	0x1079575a, 0xc71b5bdf, 0x65cc4811, 0xb2ae4494, 0xf6b612a1, 0x21d41e24,
	0x83030dea, 0x5461016f, 0x1ddc2c37, 0xcabe20b2, 0x6869337c, 0xbf0b3ff9,
	0xe0599f16, 0x373b9393, 0x95ec805d, 0x428e8cd8, 0x0b33a180, 0xdc51ad05,
	0x7e86becb, 0xa9e4b24e, 0xedfce47b, 0x3a9ee8fe, 0x9849fb30, 0x4f2bf7b5,
	0x0696daed, 0xd1f4d668, 0x7323c5a6, 0xa441c923, 0xcd868478, 0x1ae488fd,
	0xb8339b33, 0x6f5197b6, 0x26ecbaee, 0xf18eb66b, 0x5359a5a5, 0x843ba920,
	0xc023ff15, 0x1741f390, 0xb596e05e, 0x62f4ecdb, 0x2b49c183, 0xfc2bcd06,
	0x5efcdec8, 0x899ed24d, 0xd6cc72a2, 0x01ae7e27, 0xa3796de9, 0x741b616c,
	0x3da64c34, 0xeac440b1, 0x4813537f, 0x9f715ffa, 0xdb6909cf, 0x0c0b054a,
	0xaedc1684, 0x79be1a01, 0x30033759, 0xe7613bdc, 0x45b62812, 0x92d42497,
	0x9638b2a4, 0x415abe21, 0xe38dadef, 0x34efa16a, 0x7d528c32, 0xaa3080b7,
	0x08e79379, 0xdf859ffc, 0x9b9dc9c9, 0x4cffc54c, 0xee28d682, 0x394ada07,
	0x70f7f75f, 0xa795fbda, 0x0542e814, 0xd220e491, 0x8d72447e, 0x5a1048fb,
	0xf8c75b35, 0x2fa557b0, 0x66187ae8, 0xb17a766d, 0x13ad65a3, 0xc4cf6926,
	0x80d73f13, 0x57b53396, 0xf5622058, 0x22002cdd, 0x6bbd0185, 0xbcdf0d00,
	0x1e081ece, 0xc96a124b, 0xa0ad5f10, 0x77cf5395, 0xd518405b, 0x027a4cde,
	0x4bc76186, 0x9ca56d03, 0x3e727ecd, 0xe9107248, 0xad08247d, 0x7a6a28f8,
	0xd8bd3b36, 0x0fdf37b3, 0x46621aeb, 0x9100166e, 0x33d705a0, 0xe4b50925,
	0xbbe7a9ca, 0x6c85a54f, 0xce52b681, 0x1930ba04, 0x508d975c, 0x87ef9bd9,
	0x25388817, 0xf25a8492, 0xb642d2a7, 0x6120de22, 0xc3f7cdec, 0x1495c169,
	0x5d28ec31, 0x8a4ae0b4, 0x289df37a, 0xffffffff,
};

static uint32_t crc_ieee_zero_expect[] = {
	0x00000000, 0xd202ef8d, 0x41d912ff, 0xff41d912
};

/* Runs 517 tests. */
static void test_crc32(uint32_t (*crc)(uint32_t, const void *, size_t),
		       const uint32_t *(*crc_table)(void),
		       const uint32_t zero_expect[4],
		       const uint32_t four_char_expect[256],
		       const uint32_t *table_expect)
{
	unsigned int i;
	char c[4] = { 0 };

	for (i = 0; i < 4; i++)
		ok1(crc(0, c, i) == zero_expect[i]);

	for (i = 0; i < 256; i++) {
		memset(c, i, sizeof(c));
		ok1(crc(0, c, sizeof(c)) == four_char_expect[i]);
		/* CRC in two parts should give same answer. */
		ok1(crc(crc(0, c, i%5), c+i%5, 4 - (i%5))
		    == four_char_expect[i]);
	}
	ok1(memcmp(crc_table(), table_expect, 1024) == 0);
}

int main(int argc, char *argv[])
{
	plan_tests(517 * 2);
	test_crc32(crc32c, crc32c_table,
		   crcc_zero_expect, crcc_expect, crc32c_tab);
	test_crc32(crc32_ieee, crc32_ieee_table,
		   crc_ieee_zero_expect, crc_ieee_expect, crc32_ieee_tab);
	return exit_status();
}
