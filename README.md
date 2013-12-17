dups
====

Status - alpha

Find duplicate text blocks in text files. dups scans one or more directories for text files and identifies duplicate text blocks based on a minimum threshold (6)
```
usage:
   dups [options] paths

Options:
command-line-options:
  -h [ --help ]         Display this message of command line options and exit
  --version             Display the application version and exit
  -v [ --verbose ]      Include more details of builds and status. By default a
                        count of builds in each 'state' is printed to the 
                        console. Verbose output prints the status of each build
                        and the causes of any failures.
  --threshold arg (=6)  Threshold for duplicate discovery (default is 6)
```
