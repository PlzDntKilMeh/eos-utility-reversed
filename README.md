# eos-utility-reversed
This takes the wifi functions from the EOS Utility windows desktop app and allows you to use them with the EDSDK

I have no clue how most of this works lol. The EOS Utility is .net so I opened it in dnspy took the important code slapped it in chat gpt to convert it to c++ and it worked.

Usage:
  - On your camera go to Wireless communication settings -> wi-fi function
  - Click on the "INFO. View info" button and put the camera's mac address inside of macaddres.txt
    After that Press the menu button to go back then go to Remote control (EOS Utility) -> Select a network. Then setup your network and start pairing
  
  - Run the SetupUpnp.exe, This stays running the whole time you want to have a connection with your camera.
  - Run the ActivateCamera.exe, This is buggy and I have to rerun it a couple times. If it works your camera will give a prompt.
  - Now with the SetupUPNP.exe still running you can connect to your camera with the EDSDK over wifi
  - run capture.exe to test if everthing worked it should take a picture on your camera. Has bad error handiling run it a couple times to be sure.
