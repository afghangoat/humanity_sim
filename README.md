# NHF2 - Humanity simulator.

A simple humanity simulator which can simulate a world, where humans chose classes and develop their city and technology.
Contains a custom headless SFML library made by me.
Also supports Hungarian and English error logging.

## Features

### `mod_config.yml`

| Setting Name             | Default Value | Description                                                                 |
|--------------------------|---------------|-----------------------------------------------------------------------------|
| `debug_level`            | 3             | Mennyire legyen bőbeszédű a program debug loggere? (0: kritikus, 1: hibák, 2: figyelmeztetés, 3: minden) |
| `target_fps`             | 60            | Megcélzott képkocka per másodperc (FPS).                                   |
| `screen_width`           | 960           | A render ablak szélessége.                                                 |
| `screen_height`          | 640           | A render ablak magassága.                                                  |
| `world_size`             | 40            | Hányszor hány kocka legyen a világ (pl. 40x40).                            |
| `what_language`          | MAGYAR        | A logger nyelve. (NONE, MAGYAR, ENGLISH)                                   |
| `what_sfml_language`     | NONE          | Az SFML logger nyelve. (NONE, MAGYAR, ENGLISH)                             |
| `max_spawn_tries`        | 99            | Maximális próbálkozások száma entitások lerakására.                        |
| `hostiles_count`         | 1             | Ellenséges egységek száma.                                                 |
| `resource_scarcity`      | 4             | A nyersanyag ritkaságának szintje.                                         |
| `day_length`             | 400.0         | Egy nap hossza játékbeli időben.                                           |
| `chromatic_aberration`   | 0             | Színeltérítés effektek be-/kikapcsolása (0: ki, 1: be).                    |
| `noise`                  | 0             | Zaj effektek be-/kikapcsolása (0: ki, 1: be).                              |

### `Content`

- Humans: (Stonemason, Woddcutter, King, Farmer, Builder, Soldier/Hunter, Anglerminer, Fisherman, Idle)
- Animals: Goat, Crocodile, Bear
- Killer robot
- Resources: Bush, Tree, Iron, Stone
- Tiles: Mountain, Sea, Grass

## Compilation

On Linux (debian), run make.
Make sure sfml is installed.
If you want to run it in headless mode: `make FAKE_SFML=1`

It has ~90% test coverage (if mock sfml is not counted).
If you want test coverage measurement:

`./main
lcov --capture --directory . --output-file coverage.info
genhtml coverage.info --output-directory coverage_report`

(There are a total of 65 tests)

License: MIT