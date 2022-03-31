@echo off

SET basePath=%1

@REM These are the sub-folders that each region accesses within the destination game folder
SET US="US\root"
SET EU="EU\root"
SET JP="JP\root"
SET KR="KR\root"

set argC=0
for %%x in (%*) do Set /A argC+=1

if %argC%==3 (
    python build.py "%basePath:"=%\%US:"=%" -r US -c CLANG -o 3 -P KURIBO -s 0x80427800 -b D --shines 300 --boot %2 --out "sme_debug-us.log" %3
    @REM python build.py "%basePath:"=%\%EU:"=%" -r EU -c CLANG -o 3 -P KURIBO -s 0x80427800 -b D --shines 300 --boot %2 --out "sme_debug-eu.log" %3
    @REM python build.py "%basePath:"=%\%JP:"=%" -r JP -c CLANG -o 3 -P KURIBO -s 0x80427800 -b D --shines 300 --boot %2 --out "sme_debug-jp.log" %3
    @REM python build.py "%basePath:"=%\%KR:"=%" -r KR -c CLANG -o 3 -P KURIBO -s 0x80427800 -b D --shines 300 --boot %2 --out "sme_debug-kr.log" %3
) else (
    if %2==-v (
        python build.py "%basePath:"=%\%US:"=%" -r US -c CLANG -o 3 -P KURIBO -s 0x80427800 -b D --shines 300 --boot NONE --out "sme_debug-us.log" %2
        @REM python build.py "%basePath:"=%\%EU:"=%" -r EU -c CLANG -o 3 -P KURIBO -s 0x80427800 -b D --shines 300 --boot NONE --out "sme_debug-eu.log" %2
        @REM python build.py "%basePath:"=%\%JP:"=%" -r JP -c CLANG -o 3 -P KURIBO -s 0x80427800 -b D --shines 300 --boot NONE --out "sme_debug-jp.log" %2
        @REM python build.py "%basePath:"=%\%KR:"=%" -r KR -c CLANG -o 3 -P KURIBO -s 0x80427800 -b D --shines 300 --boot NONE --out "sme_debug-kr.log" %2
    ) else (
        python build.py "%basePath:"=%\%US:"=%" -r US -c CLANG -o 3 -P KURIBO -s 0x80427800 -b D --shines 300 --boot %2 --out "sme_debug-us.log"
        @REM python build.py "%basePath:"=%\%EU:"=%" -r EU -c CLANG -o 3 -P KURIBO -s 0x80427800 -b D --shines 300 --boot %2 --out "sme_debug-eu.log"
        @REM python build.py "%basePath:"=%\%JP:"=%" -r JP -c CLANG -o 3 -P KURIBO -s 0x80427800 -b D --shines 300 --boot %2 --out "sme_debug-jp.log"
        @REM python build.py "%basePath:"=%\%KR:"=%" -r KR -c CLANG -o 3 -P KURIBO -s 0x80427800 -b D --shines 300 --boot %2 --out "sme_debug-kr.log"
    )
)