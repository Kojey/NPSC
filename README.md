# NeoPixels Sunrise Clock

## Description
This objective of this project is to create an intelligent bedside alarm clock system, called the NeoPixels Sunrise Clock (NPSC), that can promote healthy sleep cycles through proven lighting patterns. Human activity is regulated by our ‘body clock’, which in the medical field is referred to as the ‘circadian rhythm’. The circadian rhythm affects many physiological processes including eating, sleeping and rising patterns. It is also affected by the production of melatonin which is produced by the pineal gland. The pineal gland's activity is dependent of the amount of light received by the subject. The research paper _“Action Spectrum for Melatonin Regulation in Humans: Evidence for a Novel Circadian Photoreceptor”_ published by The Journal of Neuroscience have shown that
> An exposure to light, if less
than 30lux for 30 min, will not incur significant change to the production of melatonin which will thus not impact the circadian rhythm.

This project aims to use those figures to design a sunrise clock that can help to improve the sleeping patterns of the user. The light will be produced by Neopixels, which will be used to produce the light. This project will simultaNeously be investigating the suitability of Neopixels for this application. Neopixels are easily programmable and each have a broad range of colours allowing for a wide range of light intensity and colour.

## How to contribute?
+ Create merge request :smile:
+ Clone the repo using `git clone https://github.com/kojey/NPSC.git/ `

## Hardware required

## Software installation
The software can be installed in two ways:
### Using a Makefile
### Using Atolic Studio

## Repository Structure
### bibliography
This contains all research papers and documents related in the studies of the effect of light on human's sleeping cycle.
### ethics
Documents related to ethics forms for  final year project.
### hardware
#### design
All PCBs used in this project.
The electrical connections between these PCBs can be found in NPSC_hardware.diagram  
#### documentation
All component's datasheet (not yet classified by PCBs)
### mechanical
All mechanical document used for the NPSC case
### report
Report of the project.
### software
#### code/master/Libraries/NPC
Here are the library used for the NPSC. The main.c in `code/master/src` is also required to run the NPSC software. Refer to the `Software installation` for more details.
