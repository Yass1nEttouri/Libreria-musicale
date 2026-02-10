#ifndef MUSIC_PLAYLIST_H 
#define MUSIC_PLAYLIST_H

#include <stdbool.h>

//maximum capacity of playlist you can create
#define PLAYLIST_CAPACITY 100

//definition of the playlist data structure
typedef struct Playlist playlist, *playlistPTR;
struct Playlist{
    char name[45];
    unsigned int* song_indices;
    unsigned int size;
    unsigned int capacity;
    playlistPTR next;
};

void intro_playlist();

/**
 * @brief Represents a manager for a collection of playlists.
 * 
 * This structure contains an array of playlists and the size of the array.
 */
typedef struct PlaylistManager playlistmng;
struct PlaylistManager{
    playlist* playlists;
    unsigned int size;
};

/**
 * @brief Creates a new playlist or initializes an existing one.
 * 
 * @param playlist Pointer to a playlist structure to be initialized.
 *                 Can be NULL to create a new playlist, or point to an existing
 *                 playlist structure to be reset/initialized.
 * @param playlistName Pointer to a string containing the name of the playlist.
 * @param capacity The maximum number of songs that can be stored in the playlist.
 * 
 * @return Pointer to the initialized playlist structure.
 *         Returns NULL if memory allocation fails or if the input is invalid.
 * 
 * @note The caller is responsible for freeing the allocated memory using
 *       the appropriate deallocation function.
 * 
 * @see delete_playlist()
 */
playlist* create_playlist(const char* playlistName);

/**
 * @brief Deletes a playlist and frees all associated memory.
 * 
 * This function deallocates the memory used by a playlist structure,
 * including any songs or internal data it contains.
 * 
 * @param playlist Pointer to the playlist to be deleted.
 * 
 * @return void
 * 
 * @note After calling this function, the original playlist pointer should not be used.
 * @note It is recommended to assign the return value back to the pointer variable.
 * 
 * @example
 * playlist* my_playlist = create_playlist("My Music");
 * delete_playlist(my_playlist);
 */
int delete_playlist(playlistmng* mng, const char* playlistName);

/**
 * @brief Prints the contents of a playlist to standard output
 * 
 * @param playlist Pointer to the playlist structure to be printed
 * @param playlistName Pointer to a string containing the name of the playlist to display
 * 
 * @note The function will output the playlist name followed by all songs contained within it
 * @note If playlist is NULL, behavior is undefined
 */
void print_playlist(playlistmng* mng, const char* playlistName);

/**
 * @brief Creates a new playlist manager with the specified capacity.
 * 
 * @param capacity The maximum number of playlists that can be stored in the manager.
 * 
 * @return Pointer to the initialized playlist manager structure.
 *         Returns NULL if memory allocation fails.
 * 
 * @note The caller is responsible for freeing the allocated memory using
 *       the appropriate deallocation function.
 * 
 * @see delete_playlist_manager()
 */
playlistmng* create_playlist_manager(unsigned int capacity);

/**
 * @brief Adds a playlist to the playlist manager.
 * 
 * @param mng Pointer to the playlist manager to which the playlist will be added.
 * @param p Pointer to the playlist to be added to the manager.
 * 
 * @return true if the playlist was successfully added to the manager, false otherwise.
 *         Returns false if the manager is full or if the playlist is NULL.
 */
int add_playlist_to_manager(playlistmng* mng, playlist* p);

/**
 * @brief Adds a song to an existing playlist.
 * 
 * @param playlistName The name of the playlist to which the song will be added.
 * @param song_index The index of the song to be added to the playlist.
 * 
 * @return true if the song was successfully added to the playlist, false otherwise.
 *         Returns false if the playlist does not exist or if the song index is invalid.
 */
bool add_song_to_playlist(char* playlistName, unsigned int song_index);

/**
 * @brief Removes a song from a playlist at the specified index.
 * 
 * @param playlistName Pointer to a null-terminated string containing the name of the playlist.
 * @param song_index The index of the song to be removed from the playlist.
 * 
 * @return true if the song was successfully deleted from the playlist, false otherwise.
 *         May return false if the playlist is not found or the index is out of bounds.
 */
bool delete_song_from_playlist(char* playlistName, unsigned int song_index);

/**
 * @brief Displays all playlists in the system
 * 
 * Iterates through the array of playlists and prints information about each one,
 * including playlist names, number of songs, and other relevant details.
 * 
 * @param playlists Pointer to the first element of the playlist array to be displayed
 * 
 * @return void
 * 
 * @note If playlists is NULL, behavior is undefined
 */
void show_all_playlists(playlistmng* mng);

#endif