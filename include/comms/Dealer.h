#ifndef __DEALER_H_
#define __DEALER_H_

typedef struct Card card_t;
typedef unsigned int PlayerID_t

bool sendCard(PlayerID_t _player, card_t _card);
bool sendBetLimits(PlayerID_t _player, unsigned int _min, unsigned int _max);
bool sendMonday(PlayerID_t _player, unsigned int _amount);

bool recieveBet(PlayerID_t _player, unsigned int *_bet, unsigned int _timeout = 4);
bool recieveCard(PlayerID_t _player, card_t *_card, unsigned int _timeout = 4);
bool recievePlayerCount(PlayerID_t _player, unsigned int *_players, unsigned int _timeout = 4);
bool recieveName(PlayerID_t _player, char **_name, unsigned int _timeout = 4);

/* ========== Usage example ==========
 * unsigned int result;
 * PlayerID_t player = 0;
 *
 * if( !recieveBet(player, &result) )
 * {
 *    printf("Player %d failed to respond to bet request\n");
 *    // Kick from game or move on to next player?
 * } 
 * else
 * {
 *    doBet(result);
 * }
 */

#endif
