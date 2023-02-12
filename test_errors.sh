#!/bin/bash
# Bash script

echo "test all parsing errors"
echo
echo
echo
echo "< test_maps/error_maps/comment_after_end*****$$$$"
./lem-in < test_maps/error_maps/comment_after_end
echo
echo
echo
echo "< test_maps/error_maps/comment_after_start*****$$$$"
./lem-in < test_maps/error_maps/comment_after_start
echo
echo
echo
echo "./lem-in < test_maps/error_maps/comment_in_link*****$$$$"
./lem-in < test_maps/error_maps/comment_in_link
echo
echo
echo
echo "./lem-in < test_maps/error_maps/comment_in_room*****$$$$"
./lem-in < test_maps/error_maps/comment_in_room
echo
echo
echo
echo
echo "./lem-in < test_maps/error_maps/empty_file*****$$$$"
./lem-in < test_maps/error_maps/empty_file
echo
echo
echo
echo
echo "./lem-in < test_maps/error_maps/empty_line_after_ants*****$$$$"
./lem-in < test_maps/error_maps/empty_line_after_ants
echo
echo
echo
echo
echo "./lem-in < test_maps/error_maps/empty_line_between_rooms_and_links*****$$$$"
./lem-in < test_maps/error_maps/empty_line_between_rooms_and_links
echo
echo
echo
echo
echo "./lem-in < test_maps/error_maps/empty_line_in_links*****$$$$"
./lem-in < test_maps/error_maps/empty_line_in_links
echo
echo
echo
echo
echo "./lem-in < test_maps/error_maps/empty_line_in_rooms*****$$$$"
./lem-in < test_maps/error_maps/empty_line_in_rooms
echo
echo
echo
echo
echo "./lem-in < test_maps/error_maps/end_after_end*****$$$$"
./lem-in < test_maps/error_maps/end_after_end
echo
echo
echo
echo
echo "./lem-in < test_maps/error_maps/end_after_start*****$$$$"
./lem-in < test_maps/error_maps/end_after_start
echo
echo
echo
echo
echo "./lem-in < test_maps/error_maps/invalid_ants*****$$$$"
./lem-in < test_maps/error_maps/invalid_ants
echo
echo
echo
echo
echo "./lem-in < test_maps/error_maps/invalid_room_coordinate*****$$$$"
./lem-in < test_maps/error_maps/invalid_room_coordinate
echo
echo
echo
echo
echo "./lem-in < test_maps/error_maps/invalid_room_in_link_0*****\n\n\n"
./lem-in < test_maps/error_maps/invalid_room_in_link_0
echo
echo
echo
echo
echo "./lem-in < test_maps/error_maps/invalid_room_in_link_1*****\n\n\n"
./lem-in < test_maps/error_maps/invalid_room_in_link_1
echo
echo
echo
echo
echo "./lem-in < test_maps/error_maps/invalid_room_in_link_2*****\n\n\n"
./lem-in < test_maps/error_maps/invalid_room_in_link_2
echo
echo
echo
echo
echo "./lem-in < test_maps/error_maps/invalid_room_name_0*****\n\n\n"
./lem-in < test_maps/error_maps/invalid_room_name_0
echo
echo
echo
echo
echo "./lem-in < test_maps/error_maps/link_after_end*****\n\n\n"
./lem-in < test_maps/error_maps/link_after_end
echo
echo
echo
echo
echo
echo "./lem-in < test_maps/error_maps/link_after_start*****\n\n\n"
./lem-in < test_maps/error_maps/link_after_start
echo
echo
echo
echo
echo "./lem-in < test_maps/error_maps/link_among_rooms*****\n\n\n"
./lem-in < test_maps/error_maps/link_among_rooms
echo
echo
echo
echo
echo "./lem-in < test_maps/error_maps/missing_room_coordinate*****\n\n\n"
./lem-in < test_maps/error_maps/missing_room_coordinate
echo
echo
echo
echo
echo "./lem-in < test_maps/error_maps/my_test1*****\n\n\n"
./lem-in < test_maps/error_maps/my_test1
echo
echo
echo
echo
echo "./lem-in < test_maps/error_maps/negative_ants*****\n\n\n"
./lem-in < test_maps/error_maps/negative_ants
echo
echo
echo
echo
echo "./lem-in < test_maps/error_maps/no_ants*****\n\n\n"
./lem-in < test_maps/error_maps/no_ants
echo
echo
echo
echo
echo "./lem-in < test_maps/error_maps/no_end*****\n\n\n"
./lem-in < test_maps/error_maps/no_end
echo
echo
echo
echo
echo "./lem-in < test_maps/error_maps/no_links*****\n\n\n"
./lem-in < test_maps/error_maps/no_links
echo
echo
echo
echo
echo "./lem-in < test_maps/error_maps/no_path_from_start_to_end"
./lem-in < test_maps/error_maps/no_path_from_start_to_end
echo
echo
echo
echo
echo "./lem-in < test_maps/error_maps/no_rooms*****\n\n\n"
./lem-in < test_maps/error_maps/no_rooms
echo
echo
echo
echo
echo "./lem-in < test_maps/error_maps/no_start*****\n\n\n"
./lem-in < test_maps/error_maps/no_start
echo
echo
echo
echo
echo "./lem-in < test_maps/error_maps/room_among_links*****\n\n\n"
./lem-in < test_maps/error_maps/room_among_links
echo
echo
echo
echo
echo "./lem-in < test_maps/error_maps/room_starts_with_L*****\n\n\n"
./lem-in < test_maps/error_maps/room_starts_with_L
echo
echo
echo
echo
echo "./lem-in < test_maps/error_maps/same_link_twice*****\n\n\n"
./lem-in < test_maps/error_maps/same_link_twice
echo
echo
echo
echo
echo "./lem-in < test_maps/error_maps/same_room_twice*****\n\n\n"
./lem-in < test_maps/error_maps/same_room_twice
echo
echo
echo
echo
echo "./lem-in < test_maps/error_maps/start_after_end*****\n\n\n"
./lem-in < test_maps/error_maps/start_after_end
echo
echo
echo
echo
echo
echo "./lem-in < test_maps/start_after_start*****\n\n\n"
./lem-in < test_maps/start_after_start
echo
echo
echo
echo
echo "./lem-in < test_maps/error_maps/two_ends*****\n\n\n"
./lem-in < test_maps/error_maps/two_ends
echo
echo
echo
echo
echo "./lem-in < test_maps/error_maps/two_starts*****\n\n\n"
./lem-in < test_maps/error_maps/two_starts
echo
echo
echo
echo


echo "test finished collect your tears"
