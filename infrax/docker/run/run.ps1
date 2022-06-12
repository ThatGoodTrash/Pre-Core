function get-size {
	$title = "Which docker image would you like to pull down:."
	$prompt = (Write-Host "[?] Choose a cnodp/wolves image size [slim, partial, full]: " -ForegroundColor DarkMagenta -NoNewLine)
	$choices = [System.Management.Automation.Host.ChoiceDescription[]] @("&slim", "&partial", "&full")
	$default = 2
	$choice = $host.UI.PromptForChoice($title, $prompt, $choices, $default)
	Switch ($choice) {
		0 { $size="slim" }
		1 { $size="partial" }
		2 { $size="full" }
	}
	return $size
}

function get-port {
	$port = $(Write-Host "[?] Enter the port number to expose for the code-server [8080]: " -ForegroundColor DarkMagenta -NoNewLine; Read-Host)
	if (!$port) {
		return 8080
	} else {
		return $port
	}
}

function write-compose($size, $port) {
	Copy-Item $PSScriptRoot/docker-compose-template.yml $PSScriptRoot/docker-compose.yml -Force 
	(Get-Content $PSScriptRoot/docker-compose.yml).replace('${WOLF_SIZE}', $size).replace('${EXPOSE_PORT}', $port) | Set-Content $PSScriptRoot/docker-compose.yml

}

function start-container {
	set-location $PSScriptRoot
	docker-compose up -d 
}

function ask-server {
	$title = "Can start a vscode server on the docker instance if you would like."
	$prompt = (Write-Host "[?] Would you like to start the vscode-server now? [y/N]: " -ForegroundColor DarkMagenta -NoNewLine)
	$choices = [System.Management.Automation.Host.ChoiceDescription[]] @("&yes", "&no")
	$default = 1
	$choice = $host.UI.PromptForChoice($title, $prompt, $choices, $default)
	Switch ($choice) {
		0 { $start="yes" }
		1 { $start="no" }
	}
	return $start
}

function start-server($start, $size, $port) {
	if ($start -eq 'yes') {
		Start-Job { docker exec -t cnodp-$size  /app/code-server/bin/code-server --auth none --bind-addr 0.0.0.0:$port --user-data-dir /root/.vscode /home/precore } 
		$ip = (Get-NetIpAddress -InterfaceIndex (Get-NetRoute -DestinationPrefix 0.0.0.0/0).InterfaceIndex | where AddressFamily -eq IPv4).IPAddress
		Write-Host "[+] Connect to the code-server by navigating to http://localhost:${port} or http://${ip}:${port}" -ForegroundColor DarkGreen
	} else {
		Write-Host "[*] If you would like to start the server at another point in time run the following commands:" -ForegroundColor DarkBlue
		Write-Host "docker exec -td cnodp-$size /app/code-server/bin/code-server --auth none --bind-addr 0.0.0.0:8080 --user-data-dir /root/.vscode /home/precore" -ForegroundColor Cyan
	}	
}


function print-info($size) {
	Write-Host "Printing Info"
}
# Start code server function now 

$size = get-size
$port = get-port
write-compose $size $port
start-container
$start = ask-server
start-server $start $size $port 




# Display connection line and other pertinent information (how to stop/restart/delete entirely)
