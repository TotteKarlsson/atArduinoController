#! /bin/bash
echo "Hello Bash"

echo "Arg1: "$1
echo "Arg2: "$2
echo "Arg3: "$3
echo "Arg4: "$4

OUTPUTDIR=`cygpath $1`
APP_RELEASES=`cygpath $2`
OUTPUTFILENAME=$3
BDSCOMMONDIR=$4

echo "OUTPUTDIR: "$OUTPUTDIR
echo "AppReleases: "$APP_RELEASES
echo "Outputfilename: "$OUTPUTFILENAME
echo "BDSCOMMONDIR: "$BDSCOMMONDIR

#Extract version
VERSION=`cat ../VERSION.txt | tr -d '\r'`
APPNAME=atDB
echo "Copy stuff"
mkdir $APP_RELEASES/$APPNAME

dest=$APP_RELEASES/$APPNAME

cp ./../*.txt $dest
cp $OUTPUTDIR/$OUTPUTFILENAME $dest

#DS Binaries
 cp $OUTPUTDIR/mtkCommon.dll                    $dest
 cp $OUTPUTDIR/mtkMath.dll                      $dest
 cp $OUTPUTDIR/mtkIPC.dll                       $dest
 cp $OUTPUTDIR/atCore.dll                       $dest
 cp $OUTPUTDIR/atDatabase.dll                   $dest
 cp $OUTPUTDIR/atResources.dll                  $dest
 cp $OUTPUTDIR/atBarcodeReader.dll              $dest
 cp $OUTPUTDIR/atSSI.dll                        $dest

 cp $BDSCOMMONDIR/BPL/atVCLCore.bpl             $dest    
 cp $BDSCOMMONDIR/BPL/DuneComponentsDD.bpl      $dest
 cp $BDSCOMMONDIR/BPL/DuneFormsDD.bpl           $dest
 cp $BDSCOMMONDIR/BPL/VCLCommonDD.bpl           $dest

#Borland Packages and dll's
BC_REDIST="/cygdrive/c/CodeGear/Tokyo/bin"

cp $BC_REDIST/borlndmm.dll                      $dest
cp $BC_REDIST/cc32250mt.dll                     $dest
cp $BC_REDIST/midas.dll                         $dest

suffix="250.bpl"
cp $BC_REDIST/bindcomp$suffix                   $dest
cp $BC_REDIST/bindcompvcl$suffix                $dest
cp $BC_REDIST/bindengine$suffix                 $dest
cp $BC_REDIST/dbexpress$suffix                  $dest
cp $BC_REDIST/dbrtl$suffix                      $dest
cp $BC_REDIST/dbxcds$suffix                     $dest
cp $BC_REDIST/DbxCommonDriver$suffix		    $dest
cp $BC_REDIST/DbxDevartPostgreSQLDriver$suffix	$dest
cp $BC_REDIST/DBXMySQLDriver$suffix		        $dest
cp $BC_REDIST/dsnap$suffix                      $dest
cp $BC_REDIST/rtl$suffix                        $dest
cp $BC_REDIST/vcl$suffix                        $dest
cp $BC_REDIST/vclactnband$suffix                $dest
cp $BC_REDIST/vcldb$suffix                      $dest
cp $BC_REDIST/vclimg$suffix                     $dest
cp $BC_REDIST/vclx$suffix                       $dest

miscRedist="/cygdrive/p/redist/atdb"
cp $miscRedist/dbexppgsql40.dll             $dest
cp $miscRedist/tsclib.dll                   $dest
cp $miscRedist/navusbapi.dll                $dest

#for local bin folder

cp $miscRedist/navusbapi.dll                $OUTPUTDIR
