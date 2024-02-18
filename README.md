# eos-utility-reversed

ONLY TESTED ON EOS 80D, Should probably work on any camera that works with the EOS Utility and EDSDK.

This takes the wifi functions from the EOS Utility windows desktop app and allows you to use them with the EDSDK

The EOS Utility is .net so I opened it in dnspy took the important code.

Usage:
  - Download the release
  - On your camera go to Wireless communication settings -> wi-fi function
  - Click on the "INFO. View info" button and put the camera's mac address inside of macaddress.txt
    After that Press the menu button to go back then go to Remote control (EOS Utility) -> Select a network. Then setup your network and start pairing
  
  - Run the SetupUpnp.exe, This stays running the whole time you want to have a connection with your camera.
  - Run the ActivateCamera.exe, This is buggy and I have to rerun it a couple times. If it works your camera will give a prompt.
  - Now with the SetupUPNP.exe still running you can connect to your camera with the EDSDK the same way you would wired but now over wifi
  - run capture.exe to test if everthing worked it should take a picture on your camera. Has bad error handling run it a couple times to be sure.

The ActivateCamera.exe only has to be ran on the first time setting up the camera or anytime you clear your camera settings.
