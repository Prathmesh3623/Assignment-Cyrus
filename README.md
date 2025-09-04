Assignment-Cyrus  - FPS Shooter Game 

Description
This project is a first-person shooter (FPS) game built in Unreal Engine 5 . The core gameplay revolves around spawning colored box targets from a JSON file, assigning them health and score values, and updating the player score dynamically via a UI widget upon successful destruction.


##  Core Logic & Features

### 1.  JSON-Based Target Spawning
- The game reads a JSON file (`Box.json`) containing:
  - **Box Types** (name, color, health, score)
  - **Spawn Transforms** (location, rotation, scale)
- Parsed using a custom C++ class: `FBoxDataLoader`
- Each box is spawned dynamically in `AShooterGameMode::BeginPlay()` using:
  - `SpawnActor<ABoxTarget>()`
  - `InitBox()` to set color, health, score

### 2.  Box Damage & Destruction
- `ABoxTarget` handles health logic
- When damage reduces health to 0:
  - The box is destroyed
  - An optional explosion particle is played
  - The GameMode is notified to update the score

### 3.  Score UI via UMG Widget
- A `ShooterWidget` (UMG blueprint) displays the live score
- Bound to a C++ class `UShooterWidget` via `CreateWidget()`
- The score is updated using `UpdateScore(int32)` called from GameMode

---

##  How to Test the Features

1. **Open the Project in Unreal Engine**
   - Open `CyrusAssignment.uproject`
   - Ensure the JSON file is in `Content/Data/Box.json`

2. **Play the Game in Editor (PIE)**
   - Press `Play`
   - Move the player and shoot the boxes

3. **Verify the Logic**
   - Boxes of different colors and health spawn
   - Shooting them reduces their health
   - Destroyed boxes disappear and trigger explosion (if set)
   - The score updates live in the top UI

---

##  Challenges Faced

1. GitHub file limit (100MB) 
--------Used .gitignore and 'git filter-repo to remove' `.vs` and `.ipch` files

   
2.UI not displaying score 
--------Corrected widget reference and ensured binding with `ShooterWidget` 


3.Crashes from missing `BeginPlay()` 
--------Implemented properly in `ABoxTarget` and derived widgets 


4. JSON loading failures 
--------Added logging and null-checks during spawn loop 

