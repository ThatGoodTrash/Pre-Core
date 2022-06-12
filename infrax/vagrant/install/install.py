#!/usr/bin/python3
import argparse
import platform
import shlex
import subprocess

providers = [
    "none",
    "virtualbox",
    "vmware",
    "both"
]

def parseargs():
    parser = argparse.ArgumentParser(description='Simple interface for initializing and running CNODP vagrant VM.')
    parser.add_argument('-p',
                        '--provider', 
                        choices=providers,
                        default='none',
                        help='The provider to install on the box. Not required if virtualbox or vmware is already installed on the host machine.')
    return vars(parser.parse_args())   

def install_vagrant(sys):
    vagrant_nix_cmds = [
        'curl -fsSL https://apt.releases.hashicorp.com/gpg | sudo apt-key add -',
        'sudo apt-add-repository "deb [arch=amd64] https://apt.releases.hashicorp.com $(lsb_release -cs) main"',
        'sudo apt-get update && sudo apt-get install -y vagrant'
    ]
    vagrant_win_cmds = [
        'powershell -command "& {Set-ExecutionPolicy Bypass -Scope Process -Force; iex ((New-Object System.Net.WebClient).DownloadString(\'https://chocolatey.org/install.ps1\'))}"',
        'cinst vagrant'
    ]

    cmds = vagrant_win_cmds if sys == "Windows" else vagrant_nix_cmds

    for cmd in cmds:
        subprocess.run(shlex.split(cmd))

def install_provider(sys, provider):
    if provider == 'none':
        return
    
    cmds = [] 
    if sys == 'Windows':
        if provider == 'virtualbox' or provider == 'both':
            cmds += ['cinst virtualbox']
        if provider == 'vmware' or provider == 'both': 
            cmds += ['cinst vmwareworkstation',
                     'powershell -command "& {Invoke-WebRequest -Uri https://releases.hashicorp.com/vagrant-vmware-utility/1.0.21/vagrant-vmware-utility_1.0.21_x86_64.msi -outfile ./vagrant-vmware-utility.msi}"',
                     './vagrant-vmware-utility.msi /passive',
                     'net.exe start vagrant-vmware-utility',
                     'vagrant plugin install vagrant-vmware-desktop'
                    ]
    else:
        if provider == 'virtualbox' or provider == 'both':
            cmds += ['sudo apt-get install -y virtualbox']
        if provider == 'vmware' or provider == 'both': 
            cmds += ['wget -nv -O vagrant-vmware-utility.zip https://releases.hashicorp.com/vagrant-vmware-utility/1.0.21/vagrant-vmware-utility_1.0.21_linux_amd64.zip',
                     'sudo mkdir -p /opt/vagrant-vmware-desktop/bin',
                     'sudo unzip -d /opt/vagrant-vmware-desktop/bin vagrant-vmware-utility.zip',
                     'sudo /opt/vagrant-vmware-desktop/bin/vagrant-vmware-utility certificate generate',
                     'sudo /opt/vagrant-vmware-desktop/bin/vagrant-vmware-utility service install',
                     'vagrant plugin install vagrant-vmware-desktop'
                    ]
    
    for cmd in cmds:
        subprocess.run(shlex.split(cmd))

if __name__ == "__main__":
    args = parseargs()
    sys = platform.system()
    install_vagrant(sys)
    install_provider(sys, args['provider'])
