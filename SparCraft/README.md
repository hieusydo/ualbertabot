SparCraft - 2013
David Churchill - dave.churchill@gmail.com


For documentation please visit:

https://code.google.com/p/sparcraft/


## Notes on setting up SparCraft
- Fix `SDL.h not found` error: 
  - Download source of [SDL](https://www.libsdl.org/download-2.0.php) and [SDL_image](https://www.libsdl.org/projects/SDL_image/)
  - Add directories by right-click on project `Properties > Configuration Properties > VC++ Directories`. Update `Include Directories` by adding `include` folder from the sources. Do the same for `Libraries Directories` by adding `SparCraft/lib`  and `Source Directories` by adding `SparCraft/source`.
- Build as `Release` and `Win32`. 
- To run `bin/SparCraft.exe` from `Cmd`, need to include these in the same folder:
  - `SDL2.dll` and `SDL2_image.dll` (downloaded from the same site of the source codes)
  - `<experiment-config>.txt` file. Must change the paths in the experiment config file. 

## Notes on running UAbertaBot
- Might need to use [iCCup](https://iccup.com/starcraft/content/news/iccup_updated_to_1.16.1.html) to run SC:BW 1.16.1
- Comprehensive [instructions](https://github.com/davechurchill/ualbertabot/wiki/Installation-Instructions) by Churchil