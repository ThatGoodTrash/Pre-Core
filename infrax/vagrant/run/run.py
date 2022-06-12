#!/usr/bin/python3
import argparse
import os
import shlex
import subprocess
import sys

from pathlib import Path 

providers = [
    'virtualbox',
    'vmware'
]

def parseargs():
    parser = argparse.ArgumentParser(description='Simple interface for initializing and running CNODP vagrant VM.')
    parser.add_argument('-p',
                        '--provider', 
                        choices=providers,
                        default='virtualbox',
                        help='The provider to utilize when starting the box.')
    parser.add_argument('-c',
                        '--cpus', 
                        metavar='cpus',
                        type=int, 
                        default=2,
                        help='The amount of vCPUs to start the box with. Amount must be between 1-8 vCPUs.')
    parser.add_argument('-r',
                        '--ram', 
                        metavar='ram',
                        type=int, 
                        default=4,
                        help='The amount of RAM to start the box with. Amount must be between 2-32 GBs.')
    parser.add_argument('-d',
                        '--dir', 
                        metavar='directory',
                        type=str, 
                        default=f"{Path.home()}/vagrant-vms/cnodp",
                        help='The path to store the Vagrantfile and where to run the vagrant up command. If you wish to use the vagrant commands against the box after deployment you must run the commands from this directory.')
    parser.add_argument('-f',
                        '--force', 
                        action='store_true',
                        help='If a Vagrantfile already exists in the destination directory force overwrite it and continue with the build.')
    return vars(parser.parse_args())

def validateargs(cpus, ram, dir, force):
    if cpus < 1 or cpus > 8:
        print(f"The number of vCPUs requested: {cpus} is not allowed. Please pick a number between 1-8 vCPUs.")
        sys.exit()

    if ram < 2 or ram > 32:
        print(f"The amount of RAM requested: {ram} is not allowed. Please pick an amount between 2-32 GBs")
        sys.exit()

    if not Path(dir).exists():
        try:
            Path(dir).mkdir(parents=True)
        except Exception as e:
            print(
                f"The provided directory: {dir} did not exist and was not able to be created. "
                f"Please check the path and try again.\n"
                f"The given error was:\n{e}"
            )
            sys.exit()
    else:
        if Path(f"{dir}/Vagrantfile").exists():
            if force:
                os.remove(f"{dir}/Vagrantfile")
            else:
                print(
                    f"The chosen directory: {dir} already has a Vagrantfile. "
                    f"Refusing to run. If you would like to overwrite the Vagrantfile "
                    f"Add the 'force' flag to your command and re-run."
                )
                sys.exit()

def initialize_vagrant(dir):
    subprocess.run(
        shlex.split("vagrant init cnodp/wolves"),
        cwd=dir
    )

def update_vagrantfile(dir, ram, cpus):
    content = []
    with open("Vagrantfile", "r") as f:
        content = f.readlines()
    
    ram = ram * 1024
    ncontent = []
    for line in content:
        nline = line.replace("vb.memory =", f"vb.memory = {ram} #")
        nline = nline.replace("vb.cpus =", f"vb.cpus = {cpus} #")
        nline = nline.replace("vb.vmx[\"memsize\"] =", f"vb.vmx[\"memsize\"] = \"{ram}\" #")
        nline = nline.replace("vb.vmx[\"numvcpu\"] =", f"vb.vmx[\"numvcpu\"] = \"{cpus}\" #")
        ncontent.append(nline)

    with open(f'{dir}/Vagrantfile', "w") as f:
        f.writelines(ncontent)

def start_vm(dir, provider):
    provider = provider if provider != 'vmware' else 'vmware_desktop'
    subprocess.run(
        shlex.split(f"vagrant up --provider {provider}"),
        cwd=dir
    )

if __name__ == "__main__":
    args = parseargs()
    validateargs(args['cpus'], args['ram'], args['dir'], args['force'])
    initialize_vagrant(args['dir'])
    update_vagrantfile(args['dir'], args['ram'], args['cpus'])
    start_vm(args['dir'], args['provider'])