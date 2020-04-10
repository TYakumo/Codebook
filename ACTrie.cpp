class ACTrieNode {
	const int MAXC = 26;
public:
    vector <ACTrieNode*> c;
    ACTrieNode* flink;
    bool endOfString;

    ACTrieNode() {
        c = move(vector <ACTrieNode*>(MAXC));
        endOfString = false;
        flink = nullptr;
    }
};

void addPattern(ACTrieNode* node, string& s) {
    for (int i = 0; i < s.size(); ++i) {
        int ch = s[i] - 'a';

        if (node->c[ch] == nullptr) {
            node->c[ch] = new ACTrieNode();
        }

        node = node->c[ch];
    }

    node->endOfString = true;
}

void buildACTrie(ACTrieNode* root) {
    deque <ACTrieNode*> que;
    que.push_back(root);

    while (!que.empty()) {
        ACTrieNode *now = que.front();
        que.pop_front();

        for (int ch = 0; ch < 26; ++ch) {
            if (now->c[ch]) {
                ACTrieNode *fnode = now->flink;

                while (fnode && fnode->c[ch] == nullptr) {
                    fnode = fnode->flink;
                }

                if (fnode == nullptr) {
                    now->c[ch]->flink = root;
                } else {
                    now->c[ch]->flink = fnode->c[ch];
                    now->c[ch]->endOfString = now->c[ch]->endOfString || fnode->c[ch]->endOfString;
                }

                que.push_back(now->c[ch]);
            }
        }
    }
}