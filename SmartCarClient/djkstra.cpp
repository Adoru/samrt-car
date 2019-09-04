#include "animation.h"

void animation::initGraph()
{
    for(int i = 0; i < 9; i++)
    {
        pathVect[i].clear();
    }

    int graphInitData[24][2] =
    {
       {0,1}, {0,3},
       {1,0}, {1,2}, {1,4},
       {2,1}, {2,5},
       {3,0}, {3,4}, {3,6},
       {4,1}, {4,3}, {4,5}, {4,7},
       {5,2}, {5,4}, {5,8},
       {6,3}, {6,7},
       {7,4}, {7,6}, {7,8},
       {8,5}, {8,7}
    };

    for(int i = 0; i < 24; i++)
    {
        edge e;
        e.to = graphInitData[i][1];
        e.cost = 0;
        pathVect[graphInitData[i][0]].push_back(e);
    }
}

/***********************************
 * djkstra 规划路径
 * 将规划好的路径存放到 minPath 中
 ***********************************/
void animation::djkstra(int start, int end)
{
    QQueue<int> queue;
    QVector<int> exploredVect;  //记录已被拓展节点
    int minCostNode;            //记录每次拓展时花费最小的节点

    for(int i = 0; i < 9; i++)
    {
        pathArray[i].clear();
        for(int j = 0; j < 9; j++)
        {
            pathWeightArray[i][j] = 99;
        }
    }
    minPath.clear();

    queue.push_back(start);
    minCostNode = pathVect[start][0].to;
    exploredVect.push_back(start);

    for(int i = 0; i < 9; i++)
    {
        pathArray[i].push_back(start);        //记录最短路的的数组第一列为start
        pathWeightArray[i][start] = 0;        //起点到起点距离为零
    }

    for(int i = 0; i < 9; i++)
    {
        int minCost = 99;                               //比较每次拓展各节点的花费情况
        foreach (edge e, pathVect[queue.front()])       //遍历拓展节点的所有边
        {
            if((e.cost + pathWeightArray[start][queue.front()]) < pathWeightArray[queue.front()][e.to]
                    && endNodeNotExplored(exploredVect ,e.to))
            {
                for(int j = 0; j < 9; j++)
                {
                    pathWeightArray[j][e.to] = e.cost
                            + pathWeightArray[start][queue.front()];  //如果最小距离需要更新，更新一整列
                }

                //更新最短路径
                pathArray[e.to].clear();
                foreach (int a, pathArray[queue.front()])
                {
                    pathArray[e.to].push_back(a);
                }
                pathArray[e.to].push_back(e.to);
                //qDebug() << "更新：" << pathArray[e.to];
            }

            if(e.cost < minCost && endNodeNotExplored(exploredVect ,e.to))
            {

                minCost = e.cost;
                minCostNode = e.to;
            }
        }
        exploredVect.push_back(minCostNode);
        queue.push_back(minCostNode);
        queue.pop_front();
    }

    //得到最短路径
    minPath.clear();
    foreach (int a, pathArray[end]) {
        minPath.append(a);
    }
}

/***********************************
 * 判断节点是否已被扩展
 ***********************************/
bool animation::endNodeNotExplored(QVector<int> vect, int node)
{
    foreach (int isNode, vect)
    {
        if(isNode == node) return 0;
    }
    return 1;
}













