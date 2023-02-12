#!/bin/bash
# Bash script

echo "test all parsing errors"

./lem-in < test_maps/error_maps/comment_after_end
./lem-in < test_maps/error_maps/comment_after_start
./lem-in < test_maps/error_maps/comment_in_link
./lem-in < test_maps/error_maps/comment_in_room
./lem-in < test_maps/error_maps/empty_file
./lem-in < test_maps/error_maps/empty_line_after_ants
./lem-in < test_maps/error_maps/empty_line_between_rooms_and_links
./lem-in < test_maps/error_maps/empty_line_in_links
./lem-in < test_maps/error_maps/empty_line_in_rooms
./lem-in < test_maps/error_maps/end_after_end
./lem-in < test_maps/error_maps/end_after_start
./lem-in < test_maps/error_maps/invalid_ants
./lem-in < test_maps/error_maps/invalid_room_coordinate
./lem-in < test_maps/error_maps/invalid_room_in_link_0
./lem-in < test_maps/error_maps/invalid_room_in_link_1
./lem-in < test_maps/error_maps/invalid_room_in_link_2
./lem-in < test_maps/error_maps/invalid_room_name_0
./lem-in < test_maps/error_maps/link_after_end
./lem-in < test_maps/error_maps/link_after_start
./lem-in < test_maps/error_maps/link_among_rooms
./lem-in < test_maps/error_maps/missing_room_coordinate
./lem-in < test_maps/error_maps/my_test1
./lem-in < test_maps/error_maps/negative_ants
./lem-in < test_maps/error_maps/no_ants
./lem-in < test_maps/error_maps/no_end
./lem-in < test_maps/error_maps/no_links
./lem-in < test_maps/error_maps/no_path_from_start_to_end
./lem-in < test_maps/error_maps/no_rooms
./lem-in < test_maps/error_maps/no_start
./lem-in < test_maps/error_maps/room_among_links
./lem-in < test_maps/error_maps/room_starts_with_L
./lem-in < test_maps/error_maps/same_link_twice
./lem-in < test_maps/error_maps/same_room_twice
./lem-in < test_maps/error_maps/start_after_end
./lem-in < test_maps/start_after_start
./lem-in < test_maps/error_maps/two_ends
./lem-in < test_maps/error_maps/two_starts


echo "test finished collect your tears"
