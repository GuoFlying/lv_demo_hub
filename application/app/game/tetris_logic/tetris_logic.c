
#include "tetris_logic.h"

typedef struct
{
    int8_t x;       //!< brick在地图中的x坐标
    int8_t y;       //!< brick在地图中的y坐标
    int8_t index;   //!< 方块索引, 高4位记录类型, 低4位记录变形
    uint16_t brick; //!< 方块数据
} brick_t;

#define BRICK_NUM_OF_TYPE 4 // 每一种类型有4种变形

#define BRICK_START_X ((MAP_WIDTH / 2) - (BRICK_WIDTH / 2))

#ifndef NULL
#define NULL ((void *)0)
#endif

/* Private macro -------------------------------------------------------------*/
// 对地图数组进行位操作的支持宏
#define SET_BIT(dat, bit) ((dat) |= (0x0001 << (bit)))
#define CLR_BIT(dat, bit) ((dat) &= ~(0x0001 << (bit)))
#define GET_BIT(dat, bit) (((dat) & (0x0001 << (bit))) >> (bit))

/* Private variables ---------------------------------------------------------*/
// 回调函数指针, 用来在坐标(x, y)画一个brick
static void (*draw_box)(uint8_t x, uint8_t y, uint8_t color) = NULL;
// 回调函数指针, 获取一个随机数
static uint8_t (*get_random_num)(void) = NULL;
// 回调函数指针, 返回下一个brick的信息
static void return_next_brick_info(int index);
static void (*return_next_brick_info_map)(uint8_t x, uint8_t y, uint8_t color) = NULL;
// 回调函数指针, 当有消行时调用
static void (*return_remove_line_num)(uint8_t line) = NULL;

static bool is_game_over = false;

// 方块数据表
static const uint16_t brick_table[BRICK_TYPE][BRICK_NUM_OF_TYPE] =
    {
        {0x6C00, 0x4620, 0x06C0, 0x8C40}, // S
        {0xC600, 0x2640, 0x0C60, 0x4C80}, // Z
        {0x88C0, 0xE800, 0x6220, 0x02E0}, // L
        {0x2260, 0x08E0, 0xC880, 0xE200}, // J
        {0x4444, 0x0F00, 0x2222, 0x00F0}, // I
        {0xCC00, 0xCC00, 0xCC00, 0xCC00}, // O
        {0xE400, 0x2620, 0x04E0, 0x8C80}  // T
};

// 旋转掩码表
static const uint16_t rotate_mask[BRICK_TYPE][BRICK_NUM_OF_TYPE] =
    {
        {0xEE20, 0x66E0, 0x8EE0, 0xECC0}, // S
        {0xE660, 0x2EE0, 0xEE80, 0xCCE0}, // Z
        {0xECC0, 0xEE20, 0x66E0, 0x8EE0}, // L
        {0x2EE0, 0xCCE0, 0xEE80, 0xE660}, // J
        {0x7FCC, 0xEF33, 0x33FE, 0xCCF0}, // I
        {0xCC00, 0xCC00, 0xCC00, 0xCC00}, // O
        {0xE620, 0x26E0, 0x8CE0, 0xEC80}  // T
};

// 下一个方块的y坐标初始值
static const int8_t brick_start_y[BRICK_TYPE] =
    {
        //   S   Z   L   J   I   O   T
        -2, -2, -3, -3, -4, -2, -2};

// 地图数组
// map[0]是地图的最上方
static int16_t map[MAP_HEIGHT];
// 地图备份, 保存上一次的数据, 解决屏幕闪烁问题
static int16_t map_backup[MAP_HEIGHT];

static brick_t curr_brick; // 当前方块
static brick_t next_brick; // 下一个方块

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
 * \brief  创建一个新的方块
 *
 * \return
 */
static brick_t create_new_brick(void)
{
    brick_t brick;
    uint8_t bt = get_random_num() % BRICK_TYPE;

    // 初始坐标
    brick.x = BRICK_START_X;
    brick.y = brick_start_y[bt];

    // 记录种类
    brick.index = bt << 4;
    brick.brick = brick_table[bt][0];

    return brick;
}

/**
 * \brief  将地图数组中的内容同步到屏幕, 只同步改变的部分
 */
void tetris_sync(void)
{
    uint8_t x, y;

    // 为了解决全图更新时屏幕闪烁的问题
    // 新增一个备份区, 每次只更新不一样的部分
    for (y = 0; y < MAP_HEIGHT; y++)
    {
        // 只更新不一样的部分
        if (map[y] != map_backup[y])
        {
            for (x = 0; x < MAP_WIDTH; x++)
            {
                if (GET_BIT(map[y], x) != GET_BIT(map_backup[y], x))
                    draw_box(x, y, (uint8_t)GET_BIT(map[y], x));
            }
        }
    }

    for (y = 0; y < MAP_HEIGHT; y++)
        map_backup[y] = map[y];

    return;
}

/**
 * \brief  同步所有
 */
void tetris_sync_all(void)
{
    uint8_t x, y;

    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            draw_box(x, y, (uint8_t)GET_BIT(map[y], x));
        }
    }

    return;
}

/**
 * \brief  game over?
 *
 * \return
 */
bool tetris_is_game_over(void)
{
    return is_game_over;
}

/**
 * \brief  在地图数组中画指定方块
 *
 * \param  brick
 */
static void draw_brick(const brick_t brick)
{
    uint8_t box_x, box_y;

    for (box_y = 0; box_y < BRICK_HEIGHT; box_y++)
    {
        for (box_x = 0; box_x < BRICK_WIDTH; box_x++)
        {
            // 保证在地图区域内, 因为SET_BIT()只是一个宏, 对数组边界不会进行检查
            // 所以在这里检查数组(地图)边界是必须的, 但是只要检查上边界就可以
            // 因为如果要调用此函数时已经经过冲突检测, 所以其它条件必然符合
            if (brick.y + box_y >= 0
                // && brick.y < MAP_HEIGHT
                && GET_BIT(brick.brick, 15 - (box_y * BRICK_WIDTH + box_x)))
            {
                SET_BIT(map[box_y + brick.y], box_x + brick.x);
            }
        }
    }

    return;
}

/**
 * \brief  在方块数组中清除指定方块
 *
 * \param  brick
 */
static void clear_brick(const brick_t brick)
{
    uint8_t box_x, box_y;

    for (box_y = 0; box_y < BRICK_HEIGHT; box_y++)
    {
        for (box_x = 0; box_x < BRICK_WIDTH; box_x++)
        {
            // 保证在地图区域内
            if (brick.y + box_y >= 0
                // && brick.y < MAP_HEIGHT
                && GET_BIT(brick.brick, 15 - (box_y * BRICK_WIDTH + box_x)))
            {
                CLR_BIT(map[box_y + brick.y], box_x + brick.x);
            }
        }
    }

    return;
}

/**
 * \brief  冲突检测, 检测之前要将当前方块从地图数组中清掉.
 *
 * \param  dest 目标位
 *
 * \retval true 方块在目标位有冲突
 *         false 方块在目标位无冲突
 */
static bool is_conflict(const brick_t dest)
{
    int8_t box_y, box_x;
    bool exp = true;

    for (box_y = 0; box_y < BRICK_HEIGHT; box_y++)
    {
        for (box_x = 0; box_x < BRICK_WIDTH; box_x++)
        {
            // 依次检测每一个box
            if ((GET_BIT(dest.brick, (15 - (box_y * BRICK_WIDTH + box_x)))))
            {
                // box在地图外的情况(只存在新方块刚被创建时)
                // 这时不用检测地图部分(因为没在地图内)
                // 只需要检查左右边界就可以了, 下边界也没必要检查, 因为肯定不会越界
                if ((dest.y + box_y) < 0)
                {
                    exp = (((box_x + dest.x) > (MAP_WIDTH - 1)) // 右边界
                           || ((box_x + dest.x) < 0));          // 左边界
                                                                // || ((box_y + dest.y) > (MAP_HEIGHT - 1)));  // 下边界
                }
                else
                {
                    // 此时box在地图内, 检查下边界, 还要检测box在地图内是否有冲突
                    exp = (((box_x + dest.x) > (MAP_WIDTH - 1))                  // 右边界
                           || ((box_x + dest.x) < 0)                             // 左边界
                           || ((box_y + dest.y) > (MAP_HEIGHT - 1))              // 下边界
                           || (GET_BIT(map[box_y + dest.y], (box_x + dest.x)))); // 地图内
                }
                if (exp)
                    return true;
            }
        }
    }

    return false;
}

/**
 * \brief
 *
 * \param  draw_box_to_map
 * \param  get_random
 * \param  next_brick_info
 * \param  remove_line_num
 */
void tetris_init(void (*draw_box_to_map)(uint8_t x, uint8_t y, uint8_t color),
                 uint8_t (*get_random)(void),
                 void (*next_brick_info_map)(uint8_t x, uint8_t y, uint8_t color),
                 void (*remove_line_num)(uint8_t line))
{
    uint8_t i;

    draw_box = draw_box_to_map;
    get_random_num = get_random;
    return_next_brick_info_map = next_brick_info_map;
    return_remove_line_num = remove_line_num;
    is_game_over = false;

    // 初始化地图
    for (i = 0; i < MAP_HEIGHT; i++)
        map[i] = 0;

    curr_brick = create_new_brick();
    next_brick = create_new_brick();

    // 返回预览方块信息
    return_next_brick_info(next_brick.index >> 4);

    draw_brick(curr_brick);
    tetris_sync_all();

    return;
}

/**
 * \brief  消行
 */
static void line_clear_check(void)
{
    uint8_t row, l;

    l = 0;

    // FIXME
    // 消行, map[0]实际上是地图的顶端
    // 从顶端开始向下扫, 每遇到一行满的
    // 就以此开始替换
    for (row = 0; row < MAP_HEIGHT; row++)
    {
        if (map[row] >= 0x3FF)
        {
            l++;

            uint8_t i;
            for (i = row; i > 0; i--)
            {
                map[i] = map[i - 1];
            }
            map[0] = 0;
        }
    }

    // 有消行, 返回消行数
    if (return_remove_line_num != NULL)
        return_remove_line_num(l);

    return;
}

/**
 * \brief  移动方块
 *
 * \param  direction
 *
 * \retval true 移动失败
 *         false 移动成功
 */
bool tetris_move(TETRIS_DIRE_E direction)
{
    brick_t dest_brick = curr_brick;
    bool is_move = false;

    switch ((uint8_t)direction)
    {
    case TETRIS_DIRE_LEFT:
        dest_brick.x--;
        break;
    case TETRIS_DIRE_RIGHT:
        dest_brick.x++;
        break;
    case TETRIS_DIRE_DOWN:
        dest_brick.y++;
        break;
    case TETRIS_DIRE_ROTATE:
    {
        // 低8位记录变形
        uint8_t i = dest_brick.index & 0x0F;
        i++;
        dest_brick.index = (dest_brick.index & 0xF0) | (i % 4);
        dest_brick.brick = rotate_mask[dest_brick.index >> 4][dest_brick.index & 0x0F];

        break;
    }
    default:
        break;
    }

    do
    {
        if (direction == TETRIS_DIRE_PROM_DOWN)
        {
            dest_brick.y++;
        }
        // 在检测之前先将当前方块从地图中清掉
        clear_brick(curr_brick);

        // 无冲突, 更改之
        if (!is_conflict(dest_brick))
        {
            // 旋转, 要方块信息从旋转mask改回来
            if (direction == TETRIS_DIRE_ROTATE)
            {
                dest_brick.brick = brick_table[dest_brick.index >> 4][dest_brick.index & 0x0F];
            }
            curr_brick = dest_brick;
            is_move = true;
        }
        else
        {
            is_move = false;
            // 不可移动, 且向下不可移动
            if (direction == TETRIS_DIRE_DOWN || direction == TETRIS_DIRE_PROM_DOWN)
            {
                // 先将当前方块画到地图中
                draw_brick(curr_brick);
                // 如果下落完成时当前方块还有部分在地图外
                // 或者下一个方块无法再放进地图, 游戏结束
                if (curr_brick.y + 1 <= 0)
                {
                    is_game_over = true;
                }
                // 消行
                line_clear_check();
                // 产生新方块
                curr_brick = next_brick;
                next_brick = create_new_brick();
                // 预览方块信息
                return_next_brick_info(next_brick.index >> 4);
                break;
            }
        }
    } while (direction == TETRIS_DIRE_PROM_DOWN);

    draw_brick(curr_brick);

    return is_move;
}

static void return_next_brick_info(int index)
{
    if (!return_next_brick_info_map)
    {
        return;
    }
    uint8_t x, y;
    uint8_t color = 0;
    for (y = 0; y < BRICK_HEIGHT; y++)
    {
        for (x = 0; x < BRICK_WIDTH; x++)
        {
            color = (uint8_t)GET_BIT(brick_table[index][0], x + y * BRICK_WIDTH);
            color = color == 0 ? 0 : index + 1;
            return_next_brick_info_map(x, y, color);
        }
    }
}
