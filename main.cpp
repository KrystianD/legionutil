#include <cstdio>
#include <string>

using namespace std;

string callACPI(const string& request)
{
	FILE* f = fopen("/proc/acpi/call", "w+t");
	if (!f) {
		perror("unable to open /proc/acpi/call");
		exit(2);
	}

	fprintf(f, "%s\n", request.c_str());
	char buf[200];
	size_t r = fread(buf, 1, sizeof(buf), f);
	fclose(f);

	return { buf, buf + r };
}

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, "Usage: %s command\n", argv[0]);
		fprintf(stderr, R"(
Commands: enable_rapid_charge, disable_rapid_charge
          enable_battery_conservation, disable_battery_conservation
          set_intelligent_cooling, set_extreme_performance, set_battery_saving
)");
		return 1;
	}

	string cmd = argv[1];

	if (cmd == "enable_rapid_charge") {
		callACPI("\\_SB.PCI0.LPC0.EC0.VPC0.SBMC 0x07");
	}
	else if (cmd == "disable_rapid_charge") {
		callACPI("\\_SB.PCI0.LPC0.EC0.VPC0.SBMC 0x08");
	}
	else if (cmd == "enable_battery_conservation") {
		callACPI("\\_SB.PCI0.LPC0.EC0.VPC0.SBMC 0x03");
	}
	else if (cmd == "disable_battery_conservation") {
		callACPI("\\_SB.PCI0.LPC0.EC0.VPC0.SBMC 0x05");
	}
	else if (cmd == "set_intelligent_cooling") {
		callACPI("\\_SB.PCI0.LPC0.EC0.VPC0.DYTC 0x000FB001");
	}
	else if (cmd == "set_extreme_performance") {
		callACPI("\\_SB.PCI0.LPC0.EC0.VPC0.DYTC 0x0012B001");
	}
	else if (cmd == "set_battery_saving") {
		callACPI("\\_SB.PCI0.LPC0.EC0.VPC0.DYTC 0x0013B001");
	}
	else {
		fprintf(stderr, "invalid command\n");
		return 1;
	}

	fprintf(stderr, "done\n");
	return 0;
}