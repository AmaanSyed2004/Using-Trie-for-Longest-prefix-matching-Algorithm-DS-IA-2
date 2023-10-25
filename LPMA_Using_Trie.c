#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Trie
{
    struct Trie *childNodes[2];
    char route[50];
};

struct Trie *createNode()
{
    struct Trie *newNode = (struct Trie *)malloc(sizeof(struct Trie));
    if (!newNode)
    {
        printf("Overflow Error");
    }
    else
    {
        newNode->route[0] = '\0';
        newNode->childNodes[0] = NULL;
        newNode->childNodes[1] = NULL;
    }
    return newNode;
}

void insert(struct Trie *root, const char *IPaddress, const char *route)
{
    struct Trie *curr = root;
    int len = strlen(IPaddress);

    for (int i = 0; i < len; i++)
    {
        int pos;
        if (IPaddress[i] == '1')
        {
            pos = 1;
        }
        else
        {
            pos = 0;
        }

        if (!curr->childNodes[pos])
        {
            curr->childNodes[pos] = createNode();
        }
        curr = curr->childNodes[pos];
    }
    strncpy(curr->route, route, 49);
    curr->route[49] = '\0';
}

const char *longestPrefixMatch(struct Trie *root, const char *ip)
{
    struct Trie *curr = root;
    const char *match = NULL;
    int len = strlen(ip);

    for (int i = 0; i < len; i++)
    {
        int pos;
        if (ip[i] == '1')
        {
            pos = 1;
        }
        else
        {
            pos = 0;
        }

        if (curr->route[0] != '\0')
        {
            match = curr->route;
        }
        if (!curr->childNodes[pos])
        {
            break;
        }
        curr = curr->childNodes[pos];
    }

    return match;
}

int main()
{
    struct Trie *root = createNode();

    insert(root, "192.168.1", "Route A");
    insert(root, "192.168.1.1", "Route B");
    insert(root, "192.168.1.15", "Route C");
    insert(root, "192.168.1.155", "Route D");

    const char *destinationIP = "192.168.1.150";
    const char *match = longestPrefixMatch(root, destinationIP);

    if (match)
    {
        printf("Matched Route: %s\n", match);
    }
    else
    {
        printf("No matching route found.");
    }

    return 0;
}