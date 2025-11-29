$DockerImage = "mcdanieles/lumenlab:latest"
$vidpidPatterns = "10C4:EA60", "1A86:7523", "0403:6001"
$usbList = usbipd list | Out-String

$foundDevice = $null
foreach ($pattern in $vidpidPatterns) {
  $matchLine = ($usbList -split "`n" | Where-Object { $_ -match $pattern }) | Select-Object -First 1
  if ($matchLine) {
    $foundDevice = $matchLine
    break
  }
}

if (-not $foundDevice) {
  Write-Error "No ESP32 USB device found. Plug it in and try again."
  exit 1
}

$tokens = ($foundDevice -split '\s+' | Where-Object { $_ -ne "" })
$busid = $tokens[0]
$deviceName = $tokens[3..($tokens.Length - 1)] -join " "

Write-Host "Detected ESP32 '$deviceName' on BusID $busid"

Write-Host "Loading vhci_hcd module in WSL2..."
wsl bash -c "lsmod | grep vhci_hcd || sudo modprobe vhci_hcd"

$attached = usbipd list | Out-String | Select-String "$busid.*Attached"

if ($attached) {
  Write-Host "Device $busid is already attached. Detaching..."
  usbipd detach --busid $busid
  Start-Sleep -Seconds 1
}

$bound = usbipd list | Out-String | Select-String "$busid.*Shared"
if (-not $bound) {
  Write-Host "Binding device $busid..."
  usbipd bind --busid $busid
}
else {
  Write-Host "Device $busid already shared."
}

Write-Host "Attaching device $busid to WSL..."
usbipd attach --wsl --busid $busid

$device = "/dev/ttyUSB0"
$timeoutSec = 120
$elapsed = 0
$interval = 1

Write-Host "Waiting for $device to appear..."
while ($true) {
  $exists = wsl -d Ubuntu -- bash -c "test -e $device && echo 1 || echo 0"
  if ($exists.Trim() -eq "1") {
    Write-Host "$device detected!"
    break
  }

  Start-Sleep -Seconds $interval
  $elapsed += $interval
  if ($elapsed -ge $timeoutSec) {
    Write-Error "Timeout waiting for $device. Make sure your ESP32 is connected and usbipd is running."
    exit 1
  }
}

Write-Host "$device detected!"

Write-Host "Pulling latest Docker image..."
docker pull $DockerImage

Write-Host "Running Docker container..."
docker run --rm -it -e PORT=/dev/ttyUSB0 --device='/dev/ttyUSB0:/dev/ttyUSB0' $DockerImage
