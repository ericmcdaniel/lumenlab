# Assembly Guide

The LumenLab can be physically assembled using two different methods. The first is a DIY approach, which involves manually soldering the through-hole components and ICs on to a perfboard. The other is to take the KiCad generated Gerber file and have the PCB professionally manufactured. With that option you can have the manufacturer assemble the board for you at additional cost, or you can purchase the stencil and reflow the parts on directly.

This guide's intention is to identity what components and ICs are required for both options if you want to create the LumenLab as well.

## Perfboard Prototype with Through-hole Components

Review the table listed on the [Perfboard Prototype Component Selection](prototype-component-selection.md) guide. These components are functionally equivalent (for the most part) to the SMT parts used in the manufactured version, however they typically are in the through-hole package where available for easy soldering. The one main exception is the buck converter module, MP1584. I used a off-the-shelf module for simplicity when prototyping. The main downside is that there is no package of that module available in a perfboard/breadboard friendly format, such as TO-220. The version listed in the table can instead be soldered to header pins, which I then soldered to the perfboard.

## SMT PCB Professionally Manufactured

This is currently being designed, so I don't have guidance on this yet.