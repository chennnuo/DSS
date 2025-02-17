﻿Welcome to DeepSkyStacker 5.0.1 Beta 1

This release is the start of the process of converting the code to Qt so that it can be ported to platforms other than Windows
Only 64 bit versions of Windows 7 and later are supported in this release.    So far the majority of the code for the stacking
panel has been converted to use Qt.

Here are the main changes that were made for DeepSkyStacker 5.0.1:

1. The bulk of the code for the stacking panel has been converted to Qt.  This includes a completely reworked image display.

2. The image list can now be undocked from the bottom of the stacking panel so that it operates as a separate window.

3. It is now possible to rename all groups with the exception of the initial group (Main Group).

4. Some fields in the image list (Type, ISO/Gain, and Exposure) can the double-clicked to change the values.

5. A large number of internal changes have been made with the intent of facilitating future enhancements and/or to improve processing.

6. SIMD (Single Instruction Multiple Data - also known as Advanced Vector Extensions or AVX) support for decoding raw images and for registration and stacking of RGGB images.  It delivers dramatic reductions in processing times.   As an example, Martin Toeltsch (who wrote the code) reports times to process 10 Nikon NEF files (on his computer):

	Without SIMD	52s
	Using SIMD		 8s
	
We hope to add support for GBRG images soon as this is important for Canon DSLR cameras.
	
7. Some further tuning of the OpenMP (multi-processor support) has been done.

==============================================================================================================================================
Welcome to DeepSkyStacker 4.2.5

PLEASE SCROLL DOWN TO READ THE WARNING ABOUT LIBRAW 0.20.   Please note that version 5.1.0 of DeepSkyStacker will not run on 32 bit systems or Windows XP.

Here are the main changes that were made for DeepSkyStacker 4.2.5

1. Remove use of predictive compression for TIFF files.  Use of this revealed a long standing bug in Photoshop which was able to read the files created by DSS, but then wrote corrupt TIFF files.

2. Correct a problem where DSS failed to read files whose path contained accented characters.

3. Fix for a problem where DSS incorrectly reported master calibration frames from earlier releases as being incompatible when a user specified CFA pattern was used for FITS files.

4. Fix a bug introduced in 4.2.3 which causes the code to crash when moving the sliders on the processing page.

5. Apply a development fix to the LibRaw code which was looping forever attempting to open corrupt CR3 files.

Here are the changes that were made for DeepSkyStacker 4.2.4.

1. LibRaw updated to 0.20 providing support for over 1300 cameras including Canon Eos R (.CR3 files).   CR3 file extension added to list of raw file types.
   
***** WARNING ***** WARNING ***** WARNING ***** WARNING *****
 LibRaw 0.20 has introduced a change that primarily affects users of "older" Canon DSLR cameras and FujiFilm X-Trans series cameras (older includes the EOS 60D and 60Da)!
	
The change is to increase the size of the frame area of the image that surrounds the "user area" so that top and left margins are an even number of pixels.   The resultant image that DSS extracts from the RAW file will be reduced in width, height or both by one pixel.   As result the Bayer Pattern (CFA) used for de-Bayering the image also has to change.
	
Unfortunately the LibRaw developers won't say exactly which cameras this change applies to save to say that it is not a large number.  Other have reported that at least the following cameras are definitely impacted by this change:

EOS 1D Mark IV
EOS 5D Mark II
EOS 7D
EOS 60D
EOS 550D
EOS 600D
EOS 1200D
	
If your camera is one of those affected, you will not be able to use any existing master frames produced with DeepSkyStacker 4.2.4 Beta 4 or earlier releases as they will not be compatible.   You will need to delete and re-create your master frames from the original darks, flats etc..   
	
I am sorry that this has happened, but it is outwith my control, and the LibRaw developers were not prepared to revert the change (they wouldn't even explain why they made the change).   If there were another library I could use to decode raw images I would migrate to that but after researching it over the last several days I have come up with no viable alternative.
***** WARNING ***** WARNING ***** WARNING ***** WARNING *****

2. Fix to display Exposure, f-Stop, and ISO setting from EXIF tags in TIFF files.

3. Update libtiff to 4.1.0

4. Automatic detection of CFA matrix based upon FITS keywords such as BAYERPAT, COLORTYP, and MOSAIC (for Meade DSI colour cameras).   The FITS File tab of the Raw/FITS DDP Settings dialogue has changed.   If you de-select the tick box for: "Monochrome 16 bit FITS Files are RAW files created by a DSLR or a color CCD camera", then automatic detection will be used.  You can override this by selecting this option and manually selecting the CFA pattern to be used.    All the other settings on that tab are now always available for modification.

5. The exposure time is now correctly displayed for FITS files with the exposure time in microseconds (keyword EXPOINUS).

6. Display a warning message saying that DeepSkyStacker won't de-Bayer 8-bit FITS images.

7. Change code to read TIFF files in strips instead of by scanline.  This can reduce the time to read the image by as much as a factor of 3.

8. Refactor the code to decode the TIFF file we just read and also use OpenMP.  Time to decode the image reduced by about 4-5 times.

9. Refactor the code that writes TIFF files and use OpenMP to speed it up.  Also write the output file in strips rather than scanlines and use TIFF predictive compression.  Substantial performance increase.

10. Refactor the code that reads FITS files to make it easier to understand and also use OpenMP.  Only a marginal performance benefit.

11. Major bug fix - calibration frames were either not applied or incorrectly applied when using Super-Pixel mode.

12. Change DeepSkyStackerLive so that the choice of using the Dark Theme is controlled by the user settings.

13. Display the FITS FILTER name in the picture list control, for information only at present.

14. Change the text used in the language selection ComboBox to always use Latin characters.  This is a work around a problem with DLGINIT processing and Unicode characters.

15. Fix to correct problem where jpeg files were incorrectly identified as raw.

16. When FITS file auto-detection is used, the CFA Yes/No display was incorrect - now fixed.

17. Recommended Setting for Interpolation was incorrect.

18. Fix for crash while attempting to select comet.

19. Fix for Nikon Z 6, Z 7, and Z 50 being reported as unsupported.

Welcome to DeepSkyStacker 4.2.3

************** IF YOU INSTALLED 4.2.3 BETA 1 **************
  When you next use DeepSkyStacker, please restore all
  settings to the default using:  

	Settings/Load/Restore Defaults

  before you run your stack.
*******************************************************

The main changes in this release are:

1. The 32 bit version will now run on Windows XP SP3.  It is likely that the next release of DeepSkyStacker will not do so.

2. The stacking settings dialog width has been increased to reduce or eliminate the need to scroll the tabs.

3. Add .rw2 to list of RAW file extensions.

4. Change the colour scheme for DeepSkyStacker Live to make it more "night vision" friendly.

5. Recognise and use GAIN values in FITS file from CMOS/CCD cameras in a manner similar to how ISO is handled for matching darks, lights etc..   Please note this is not the same as EGAIN (e-/ADU).  It refers to the camera's scaling of EGAIN.

6. Update help files.  My thanks to Estela Nuñez, Giovanni Benintende, Günter Heberger, José Mozart Fusco, Luc Coiffier, Михаил Тимофеев (Mickle Timofeyev), and Premysl Lukavský for their immense help with all the translation work needed for this release.   Dutch help is deferred until the next release.

7. Issue #83: Provide the option to perform NO White Balance processing at all (requested by Ivo Jager for StarTools).

8. Fix for issue #42 - the stacking method "Average" wasn't always reported in the recap html file.

9. Common control library 6 now used so some cosmetic changes such as filled progress bars.

10. Make the progress dialogs non-modal so that DeepSkyStacker can be minimised while processing.

11. Update the DeepSkyStacker taskbar icon with a progress bar that matches the main progress bar.

12. Saving of final TIFF file is now faster, and a number of other performance enhancements have been made.

13. Ctrl-A will select all images in the file list (not the same as "Check All").

14. Del key will delete an image from the file list so you don't need right click and select "Remove from list"

15. Bug fix - if you change the type of an image from the file list "Properties" dialogue, the icon was changed, but the text wasn't.

16. Bug fix - Settings were handled incorrectly in 4.2.3 Beta 1 

Welcome to DeepSkyStacker 4.2.2

This release is all about performance, though other areas have been enhanced as well.  The main changes since 4.2.1 are:

1. Changes to star registration code to detect larger stars than before.   Star radius of up to 50 pixels is now valid (it was 20 pixels).  This was needed to accomodate higher resolution sensors.

2. Allow larger star sizes to the specified in the Star Mask creation dialogue.   Star diameter of up to 100 pixels is now allowed.   This was needed to accomodate higher resolution sensors.

3. OpenMP speedup of Star Mask image reading code.

4. Huge speedup of final image display by using much larger rectangles and OpenMP speedup of the bitmap extraction code.

5. Speed up star registration by updating progress indicator once every 25 iterations instead of each iteration.

6. Computing Final Picture using Kappa-Sigma Clip processing is now about 50 times faster!

7. Computing Final Picture using Auto Adaptive Weighted Average is now about 43 times faster!

8. Auto-Adaptive Weighted Average now re-written completely.  It should no longer produce whited out images or other strange results. Thanks to Michael A. Covington and Simon C. Smith for their immense help in locating references and getting this working.  Thanks are also due to Dr. Peter B. Stetson who very kindly provided a web link to his original lecture notes, emailed a PDF copy of his original paper, and provided helpful guidance.

9. Update LibRaw to 0.19.3.

10. Reverted Entropy calculation code in CEntropyInfo::InitSquareEntropies() to NOT compute in parallel - some called code wasn't thread safe.

11. Entropy Weighted Average complete stack of 50 lights is now about 20 times faster on my laptop, down from 4hrs 22min to 12min 55 sec.

12. Bug fix - changing "Set the black point to 0" or "Use Camera White Balance" after an image was loaded didn't change the rendering.

13. When loading raw files, check that the camera is listed in the LibRaw supported camera list.  Issue a warning if not.

14. User request to change the file open dialog to default to *all* supported image types including raw files.

15. Three times performance improvement in star registration.

16. As requested by Ray Butler, use relative paths in saved file lists while continuing to accept older file lists using absolute paths.

17. Miscellaneous other performance tweaks.

18. Display lens aperture information in the image lists for DeepSkyStacker and DeepSkyStackerLive.

19. Don't check for LibRaw camera support if processing DNG file.
 
Welcome to DeepSkyStacker 4.2.1

The main changes from 4.2.0 are:

1. Fixed a memory leak in the new code that uses LibRaw.

2. Further performance enhancements to Median-Kappa-Sigma processing (20% faster than 4.2.0).

3. Entropy calculation for Entropy Weighted Average now computed in parallel.

Welcome to DeepSkyStacker 4.2.0

The main change in this release is to use LibRaw version 19.2 instead of dcraw to capture images from RAW image files.
This should provide support for many recent cameras which wasn't possible using dcraw.

The raw data post-processing code has had some extra performance squeezed out if it by Vitali Pelenjow who took
my initial attempt at using OpenMP to parallelise the code and made it perform as it should (new in 4.2.0 Beta 4).

The resulting images should be very much the same (if not 100% identical) to the results obtained using DeepSkyStacker 4.1.1.

There is one thing that is incompatible with DeepSkyStacker 4.1.1:

The "Use Auto White Balance" white balance button has been disabled.

You can either accept the default which is "Daylight White Balance", or select "Use Camera White Balance".   If you select the latter, and camera was set to "Auto White Balance" when the images were taken, then the camera calculated "Auto White Balance" co-efficients will be used.   We don't recommend the use of Auto WB as each frame gets its own unique white balance which can prevent calibration frames such as flats and darks from working correctly.

We've also fixed a number of problems and made some other enhancements since 4.1.1

1. Support for images from cameras that use the Fujitsu X-Trans sensor (new in 4.2.0 Beta 2).
   The image is converted to a 3 colour RGB image and interpolated using Frank Markesteijn's algorithm using LibRaw::Process().
   Please note that the interpolation is quite slow (about 40 seconds per image on my Core i7 laptop).
   The image is then imported as if it were a Foveon colour image.

2. BSD 3 clause license file added.

3. A fix was made to correct crashes caused by a thread-unsafe assignment in the smart pointer code.

4. The "Stop" button on the progress dialogs should now actually work!

5. The space key can now be used to check/uncheck images in the picture list.

6. The user's default browser will be used instead of IE to open URLs.

7. Miscellaneous code cleanups and performance improvements including Median-Kappa-Sigma processing.

Welcome to DeepSkyStacker 4.1.1

    The 32 bit version has been changed to build the zlib code without the optimising "asm" option to fix a crashing
	problem ("asm" is not officially supported in zlib and has not been maintained)


    The 64 bit version has been changed to build the zlib code without the optimising "asm" option as a precaution 	(the 64 bit
	version wasnt crashing as far as we know but as the "asm" option isn't officially supported we have elected not to use it)

*****

Welcome to DeepSkyStacker 4.1.0

This version of DeepskyStacker is supported on Windows 7, Windows 8, Windows 8.1 and Windows 10 and completely
supercedes DeepSkyStacker 3.3.2, 3.3.4 and 3.3.6.

We now provide DeepSkyStacker and the other programs as both 32-bit (x86) and 64-bit (x64) builds based upon the latest
version of dcraw. There are separate installers for the 32-bit and 64-bit versions.

Installing the 32-bit build will remove earlier versions of DeepSkyStacker (3.3.2 and upward). If you are running an
earlier version than 3.3.2, please remove it manually.

You can install both the 32-bit and the 64-bit versions on 64-bit versions of Windows without problems.

PLEASE NOTE: If anyone who installs this gets: "This program can't start because api-ms-win-crt-runtime-l1-1-0.dll is
missing" when they try to open the programs, the solution is to install:

https://support.microsoft.com/en-us/help/2999226/update-for-universal-c-runtime-in-windows

for your specific version of Windows.

This problem should only affect users of Vista / Win7 / Win 8.x who are behind on WindowsUpdates, or are running
an offline system and opting out of WindowsUpdates.
Enjoy,

Luc Coiffier, Tony Cook, David C. Partridge

We've fixed a number of problems since 4.1.0 beta 1:

    Fixed a problem when using drizzle and Intersection mode which resulted in an output image that was 4x or 9x
	too large with the image in the upper left corner.

    Worked around a problem with incorrect display of the left panel on high resolution monitors.
	(Set the DPI Aware flag in the application manifest to No).

    Changed our build of libtiff so that we use Unix style rather than Win32 style I/O as the Win32 code is
	wrong in x64 mode (known problem with libtiff).

    A number of other size_t/DWORD/long issues in the code were fixed for the 64 bit build (to ensure computed
	values were indeed 64 bit sized).

    Small change to improve the responsiveness of the post-processing screen (faster display of the final image).

