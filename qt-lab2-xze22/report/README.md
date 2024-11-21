# Lab2

## 项目实现说明

### `CollisionSystem.h` 和 `CollisionSystem.cpp`

#### `CollisionSystem.h`

我将 `CollisionSystem.h` 中的函数定义中的 `QVector<Ball>& balls` 替换为了 `BallList& ballList`。

#### `CollisionSystem.cpp`

在 `findCollision` 函数中，我将**用下标枚举**的循环，改为了**用链表连接**的循环。

```cpp
auto current = ballList.head;
int pos = 0;
while (current != nullptr) {
    auto currentBall = current->ball;
    float distance = ball.distanceTo(currentBall);
    if (distance < ball.getRadius() + currentBall.getRadius() + COLLISION_THRESHOLD) {
        result.hasCollision = true;
        result.collisionIndex = pos;
        break;
    }
    current = current->next;
    pos++;
}
```

在 `handleCollision` 函数中，由于我的 `BallList` 链表支持下标访问，所以仅将变量名进行了相应的修改。

### `Game.h` 和 `Game.cpp`

#### `Game.h`

我将 `Game.h` 中定义的 `BallList` 类移了出去，专门新建了 `BallList.h` 和 `BallList.cpp`。

#### `Game.cpp`

在更新路径上的球，从前向后更新时，我把 `QVector<Ball>balls` 更改为了 `BallList ballList`。可以用一个 `current` 指针从头往后枚举，以一次更新每个球的状态。

```cpp
BallList::BallNode* current = ballList.head;
while (current != nullptr) {
    float currentDistance = path.getDistanceAtPoint(current->ball.getPosition());
    float newDistance = currentDistance + BALL_SPEED * deltaTime;
    QPointF newPos = path.getPointAtDistance(newDistance);
    current->ball.setPosition(newPos);
    if (current->next != nullptr && current->ball.distanceTo(current->next->ball) > BALL_RADIUS * 2 + EPS)
        break;
    current = current->next;
}
```

我补全了 `checkMatches` 函数，它从头开始往后枚举 `begin`，统计从 `begin` 开始连续的颜色块的长度。如果长度大于等于 3，则将这一段（`[begin, current)` 左闭右开区间）删去。

```cpp
void Game::checkMatches() {
    while (ballList.size() >= 3) {
        BallList::BallNode* begin = ballList.head;
        BallList::BallNode* current = begin;
        int count = 0;
        while (current != nullptr) {
            if (current->ball.getColor() == begin->ball.getColor()) {
                count++;
            } else {
                if (count >= 3) {
                    ballList.erase(begin, current);
                    emit scoreChanged(score += count * 100);
                    break;
                }
                begin = current;
                count = 1;
            }
            current = current->next;
        }
        if (current == nullptr && count >= 3) {
            ballList.erase(begin, current);
            emit scoreChanged(score += count * 100);
        }
        if (count < 3) {
            break;
        }
    }
}
```

### `BallList.h` 和 `BallList.cpp`

#### `BallList.h`

`BallList` 是一个自定义的**链表**，用于存储和管理 `Ball` 对象。我支持了基本的链表操作，包括添加、插入、删除和清空链表。我还支持了**下标访问**。

**成员函数**：

- `append(const Ball& ball)`：在链表末尾添加一个新的 `Ball` 对象。如果链表为空，新节点成为头节点；否则，遍历到链表末尾并添加新节点。
- `insert(int index, const Ball& ball)`：在链表的指定位置插入一个新的 `Ball` 对象。如果索引为 0，新节点成为新的头节点；否则，找到指定位置的前一个节点，并在其后插入新节点。
- `erase(BallNode* begin, BallNode* end)`：删除从 `begin` 到 `end`（`[begin, current)` 左闭右开区间）的节点范围。如果 `begin` 是头节点，更新头节点；否则，找到 `begin` 的前一个节点并更新其 `next` 指针。然后，遍历并删除范围内的所有节点，更新 `m_size`。
- `operator[](int index)`：重载的下标运算符，用于访问链表中指定位置的 `Ball` 对象。如果索引超出范围，抛出 `std::out_of_range` 异常。
- `clear()`：清空链表，释放所有节点的内存，并将 `head` 设置为 `nullptr`，`m_size` 设置为 0。
- `last()`：返回链表中最后一个 `Ball` 对象的引用。如果链表为空，抛出 `std::out_of_range` 异常。
- `isEmpty()`：检查链表是否为空，返回布尔值。
- `size()`：返回链表中节点的数量。

#### `BallList.cpp`

我在 `BallList.cpp` 中实现了 `BallList.h` 中各个成员函数。

### `GameWidget.cpp`

在绘制路径上的球时，我将 `QVector<Ball>balls` 更改为了 `BallList ballList`：

```cpp
const BallList& ballList = game->getBallList();
BallList::BallNode* current = ballList.head;
while (current != nullptr) {
    QPointF pos = current->ball.getPosition();
    float radius = current->ball.getRadius();

    painter.setBrush(current->ball.getColor());
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(pos, radius, radius);

    current = current->next;
}
```

## AI 使用情况报告

我在完成此次作业的过程中**未使用 AI**。

## 大作业规划

我计划基于 Lab2 的代码进行扩展：

- 增加更多的地形
- 对于连续消除很多珠子的情形，给予道具奖励
- 添加背景音乐，并能够调整 BGM 音量大小
