function Stop-Emulators {
  Write-Host "stop emulator if needed"
  Stop-Process -Name mame64, raine32 -Force -ErrorAction SilentlyContinue
  Write-Host ""
}
