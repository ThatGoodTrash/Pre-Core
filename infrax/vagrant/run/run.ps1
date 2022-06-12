function set-cpus {
	$cpus = (Write-Host "[?] Enter the number of CPUs to assign to the VM [2]: " -ForegroundColor DarkMagenta -NoNewLine && Read-Host)
	if (!$cpus) {
		return
	}
	((Get-Content -path Vagrantfile.working -Raw) -replace "vb.cpus = 2","vb.cpus = $cpus") | Set-Content -Path Vagrantfile.working
	((Get-Content -path Vagrantfile.working -Raw) -replace 'vb.vmx["numvcpu"] = "2"', "vb.vmx[\`"numvcpu\`"] = \`"$cpus\`"") | Set-Content -Path Vagrantfile.working
}

function set-ram {
	$ram = (Write-Host "[?] Enter the amout of RAM to assign to the VM [4]: " -ForegroundColor DarkMagenta -NoNewLine && Read-Host)
	if (!$ram) {
		return
	} else {
		$ram=$ram*1024
	}
	((Get-Content -path Vagrantfile.working -Raw) -replace "vb.memory = 4096", "vb.memory = $ram") | Set-Content -Path Vagrantfile.working
	((Get-Content -path Vagrantfile.working -Raw) -replace 'vb.vmx["memsize"] = "4096"', "vb.vmx[\`"memsize\`"] = \`"$ram\`"") | Set-Content -Path Vagrantfile.working

}

function start-provider {
	$title = "About to start the VM with 'vagrant up --provider <PROVIDER>'."
	$prompt = (Write-Host "[?] Select the hypervisor provider you would like to utilize: " -ForegroundColor DarkMagenta -NoNewLine)
	$choices = [System.Management.Automation.Host.ChoiceDescription[]] @("virtualbox", "vmware")
	$default = 0
	$choice = $host.UI.PromptForChoice($title, $prompt, $choices, $default)
	Switch ($choice) {
		0 { $provider="virtualbox" }
		1 { $provider="vmware_desktop" }
	}

	Move-Item -Path Vagrantfile.working -Destination Vagrantfile -Force
	vagrant up --provider $provider
}

function initialize-vagrant {
	Write-Host "Initializing vagrant environment:" -ForegroundColor DarkBlue
	Set-Location -Path $PSScriptRoot
	if (Test-Path Vagrantfile) {
		Remove-Item -Path Vagrantfile 
	}
	if (Test-Path .vagrant) {
		Remove-Item -Path .vagrant -Recurse -Force
	} 
	vagrant init cnodp/wolves
	Copy-Item -Path Vagrantfile.template -Destination Vagrantfile.working -Force
}

initialize-vagrant
set-cpus
set-ram
start-provider