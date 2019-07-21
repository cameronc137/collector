# Similar to drawPostPan.C, but works directly from the rootLogon.C
import os
import sys
import csv
import subprocess
from argparse import ArgumentParser

parser     = ArgumentParser()
parser.add_argument("-f", "--conf", dest="devicelist", help="Device List and Analyses for camguin", required=True, metavar="DEVICELIST", default="input.txt")
parser.add_argument("-s", "--outfileName", dest="outfileName", help="Run List text file for camguin wrapper", required=True, metavar="SLUG", default="test")

args       = vars(parser.parse_args())
outfileName= args['outfileName']
devicelist = args['devicelist']

lines = []

try:
  with open(devicelist) as devicelistFile:
    for line in csv.reader(devicelistFile, delimiter=','):
      lines.append(line[0])
except:
  print("ERROR: You forgot to have a devicelist \"devicelist.txt\"\n")
  sys.exit()

print("Extracting from run " + lines[0])
os.system("root -l -b -q -x showThing.C'(\"rootfiles/prexPrompt_"+outfileName+".root\",\""+lines[0]+"\",\""+outfileName+"\")'")
os.system("mv showPrint_"+outfileName+".pdf output_"+outfileName+".pdf")
for i in range(1,len(lines)):
  print("Extracting from run " + lines[i])
  os.system("ls showPrint_"+outfileName+".pdf")
  os.system("root -l -b -q -x showThing.C'(\"rootfiles/prexPrompt_"+outfileName+".root\",\""+lines[i]+"\",\""+outfileName+"\")'")
  os.system("ls showPrint_"+outfileName+".pdf")
  os.system("mv output_"+outfileName+".pdf tmp_output_"+outfileName+".pdf")
  os.system("pdfunite tmp_output_"+outfileName+".pdf showPrint_"+outfileName+".pdf output_"+outfileName+".pdf")
  os.system("rm -f tmp_output_"+outfileName+".pdf")

os.system("mv output_"+outfileName+".pdf plots/")
