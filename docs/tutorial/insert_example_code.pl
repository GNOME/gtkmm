#! /usr/bin/perl -w

#sub main()
{
  my $examples_base = shift(@ARGV);

  $examples_base .= "/" unless($examples_base =~ /\/$/);

  foreach $file (@ARGV)
  {
    open(FILE, $file);

    while(<FILE>)
    {
      print $_;

      #Beginning of comment:
      # Look for
      # <para><ulink url="&url_examples_base;helloworld">Source Code</ulink></para>

      if(/<para><ulink url=\"&url_examples_base;([\/\w]+)\">Source Code<\/ulink><\/para>/)
      {
        #List all the source files in that directory:
        my $directory = $examples_base . $1;

        opendir(DIR, $directory);
        my @dir_contents = readdir(DIR);
        closedir(DIR);

        my @source_files = grep(/\.cc$/, @dir_contents);
        my @header_files = grep(/\.h$/,  @dir_contents);

        print "<!-- start inserted example code -->\n";

        foreach $source_file (@header_files, @source_files)
        {
           print "<para>File: ${source_file}\n";
           print "<programlisting>\n";

           &process_source_file("${directory}/${source_file}");

           print "</programlisting>\n";
           print "</para>\n";
        }

        print "<!-- end inserted example code -->\n";
      }
    }

    close(FILE);
  }

  exit 0;
}

sub process_source_file($)
{
  my ($source_file) = @_;
  my $found_start = 0;

  open(SOURCE_FILE, $source_file);

  while(<SOURCE_FILE>)
  {
    # Skip all text until the first code line.
    if(!$found_start)
    {
      next unless /^[#\w]/;
      $found_start = 1;
    }

    s/&/&amp;/g;
    s/</&lt;/g;
    s/>/&gt;/g;
    s/"/&quot;/g;

    print $_;
  }

  close(SOURCE_FILE);
}

