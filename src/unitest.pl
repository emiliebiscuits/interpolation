#!/usr/bin/perl
=pod
=head1 UNITEST
	This script propose, by using simple macros as
	TEST() and CHECK() to implement a very simple an easy to use
	unitary testing process for C and C++
=cut
use warnings;
use strict;


if (@ARGV != 1)
{
	printf("Usage : unitest input\n");
	exit(1);
}



#_____________________________________________________________________________
# VARIABLES___________________________________________________________________|
#_________/
my $input = $ARGV[0];
my $output = "src/unitest.cc";
my $functions = "#define FUNCTIONS {";
my $counter = 0;
my $type = "cpp";
my $part = "";



#_____________________________________________________________________________
# FUNCTIONS___________________________________________________________________|
#_________/
=pod
=head1 TEST_MACRO
	This function will formate a TEST(.*) line into
	a function prototype, and doing every modifications
	ever needed (increment counter, filling functions macros, etc)

=head2 ARGUMENTS
	- $str : the line to formate, TEST()
=cut
sub TEST_macro
{
	my ($str) = @_;
	my @tmp = split(/\(/, $str);
	$str = $tmp[1];
	$str =~ s/ /_/g;
	$str =~ s/[éàùèêâûî\nôïöëäü@°\/.\[\]()\{\}~\^\$%£µ§?,;|`"'!]//g;
	$str =~ s/[+]/plus/g;
	$str =~ s/-/minus/g;
	$str =~ s/\//divide/g;
	$str =~ s/[*]/multiplyby/g;
	$str =~ s/=/equal/g;
	$functions .= ", $str" unless ($counter == 0);
	$functions .= "$str" if ($counter == 0);
	$part = $str;
	$str = "void $str()";
	$counter++;
	return "$str\n";
}


=pod
=head1 CHECK_MACRO
	This function will formate a CHECK(.*) line into an exit
	point for the fresh new file.

=head2 ARGUMENTS
	- $str : the CHECK() line
	- $line : the actual line index from the original file
=cut
sub CHECK_macro
{
	my ($str, $line) = @_;
	my $expr = $str;
	$expr =~ s/[ \t]*(.*);\n/$1/;
	$str =~ s/[ \t]*CHECK\((.*)\);\n/$1/;
	$str = "\tif (!($str)){std::cerr<<\"$expr failed (line : $line), Aborting $part\"<<std::endl;return;}" unless ($type eq "c");
	$str = "\tif (!($str)){fprintf(stderr, \"$expr failed (line : $line), Aborting $part\n\");return;}" if ($type eq "c");
	return "$str\n";
}


=pod
=head1 RW_FILE
	This function will read of the input file to write the proper
	things on the output file.

=head2 ARGUMENTS
	- $fdin : a valid file descriptor for the input file
	- $fdout : a valid file descriptor for the output file
=cut
sub rw_file
{
	my ($fdin, $fdout) = @_;
	my ($str, $line) = ("", 0);
	#printf($fdout "#ifndef UNITEST_H_INCLUDED\n");
	#printf($fdout "#define UNITEST_H_INCLUDED\n");
	while (<$fdin>)
	{
		$line++;
		$str = $_;
		$type = "cpp" if ($str =~ m/^[ \t]*#include[ \t]*<.*[^.][^h]>$/);
		$type = "c" if ($str =~ m/^[ \t]*#include[ \t]*<.*\.h>$/);
		$str = CHECK_macro($str, $line) if ($str =~ m/^[ \t]*CHECK\(.*\);$/);
		$str = TEST_macro($str) if ($str =~ m/^[ \t]*TEST\(.*\)$/);
		printf($fdout "$str");
	}
	printf($fdout "\n$functions}\n#define COUNT $counter\n");
	printf($fdout "\n\nint main(void)\n{\n");
	printf($fdout "\tvoid (*f[])(void) = FUNCTIONS;\n");
	printf($fdout "\tunsigned int i = 0;\n");
	printf($fdout "\tfor(i=0;i<COUNT;++i)\n\t{\n");
	printf($fdout "\t\tf[i]();\n");
	printf($fdout "\t}\n\treturn 0;\n}\n");
	#printf($fdout "#endif");
	return 0;
}



#_____________________________________________________________________________
# MAIN SCRIPT_________________________________________________________________|
#___________/
open(my $fd_output, ">$output") or die "Unable to create the file $output ($!)\n";
open(my $fd_input, "<$input") or die "Unable to open the file $input ($!)\n";
rw_file($fd_input, $fd_output);
close($fd_input);
close($fd_output);
exit(0);
