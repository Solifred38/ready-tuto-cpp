class html_tree_data {
    constructor(_index, _parentIndex, _name, _type) {
        this.m_index        = _index;
        this.m_parentIndex  = _parentIndex;
        this.m_name         = _name;
        this.m_type         = _type;
    }

    serializeJson() {
        var lDom = {};
        lDom["index"]           = this.m_index;
        lDom["parent_index"]    = this.m_parentIndex;
        lDom["name"]            = this.m_name;
        lDom["type"]            = this.m_type;
        return JSON.stringify(lDom, null, 2);
    }

    deserializeJson(_data) {
        var lDom                = JSON.parse(_data);
        this.m_index            = lDom["index"];
        this.m_parentIndex      = lDom["parent_index"];
        this.m_name             = lDom["name"];
        this.m_type             = lDom["type"];
    }

}

class html_tree_map {
    constructor(_map) {
        this.m_map = _map;
    }

    serializeJson() {
        var lJsonMap = [];
        for(var i = 0; i < this.m_map.length; i++) {
            var lObj        = this.m_map[i];
            var lJsonData   = lObj.serializeJson();
            var lJsonObj    = JSON.parse(lJsonData);
            lJsonMap.push(lJsonObj);
        }
        return JSON.stringify(lJsonMap, null, 2);
    }

    deserializeJson(_data) {
        var lJsonMap = JSON.parse(_data);
        for(var i = 0; i < lJsonMap.length; i++) {
            var lJsonObj    = lMap[i];
            var lJsonData   = JSON.stringify(lJsonObj);
            var lObj        = new html_tree_data();
            lObj.deserializeJson(lJsonData);
            this.m_map.push(lObj);
        }
    }

}

class html_tree {
    static m_instance = null;

    static Instance() {
        if(this.m_instance == null) {
            this.m_instance = new html_tree();
        }
        return this.m_instance;
    }

    init() {
        this.initTree();
        this.initArrows();
    }

    initTree() {
        var lCarets = document.querySelectorAll(".tree3");
        for(var i = 0; i < lCarets.length; i++) {
            lCarets[i].addEventListener("click", this.onToogle);
        }

        var lDowns = document.querySelectorAll(".tree5");
        for(var i = 0; i < lDowns.length; i++) {
            lDowns[i].addEventListener("click", this.onDown);
        }

        var lUps = document.querySelectorAll(".tree6");
        for(var i = 0; i < lUps.length; i++) {
            lUps[i].addEventListener("click", this.onUp);
        }
    }

    initArrows() {
        var lLis = document.querySelectorAll(".tree1");
        for(var i = 0; i < lLis.length; i++) {
            this.updateArrows(lLis[i]);
        }
    }

    onToogle(e) {
        this.classList.toggle("down");
        var lLiMenu = this.parentElement.querySelector(".tree2");
        lLiMenu.classList.toggle("active");

        var lTree = new html_tree();
        lTree.updateArrows(lLiMenu);
    }

    onDown(e) {
        e.stopPropagation();
        var lLiCurrent = e.target.parentElement;
        if(lLiCurrent.classList.contains("tree3")) {
            lLiCurrent = lLiCurrent.parentElement;
        }
        var lLiParent = lLiCurrent.parentElement;
        var lLiDown = lLiCurrent.nextElementSibling;
        if(!lLiDown) {
            console.warn("Erreur l'élément en cours est le plus bas.");
            return;
        }
        var lLiBefore = lLiDown.nextElementSibling;
        lLiParent.removeChild(lLiCurrent);
        lLiParent.insertBefore(lLiCurrent, lLiBefore);

        var lTree = new html_tree();
        lTree.updateArrows(lLiParent);
    }

    onUp(e) {
        e.stopPropagation();
        var lLiCurrent = e.target.parentElement;
        if(lLiCurrent.classList.contains("tree3")) {
            lLiCurrent = lLiCurrent.parentElement;
        }
        var lLiParent = lLiCurrent.parentElement;
        var lLiUp = lLiCurrent.previousElementSibling;
        if(!lLiUp) {
            console.warn("Erreur l'élément en cours est le plus haut.");
            return;
        }
        lLiParent.removeChild(lLiCurrent);
        lLiParent.insertBefore(lLiCurrent, lLiUp);

        var lTree = new html_tree();
        lTree.updateArrows(lLiParent);
    }

    showArrows(_parent) {
        var lLis = _parent.querySelectorAll(":scope > li > .tree3, :scope > .tree4");
        for(var i = 0; i < lLis.length; i++) {
            var lLiCurrent = lLis[i];
            var lLiDown = lLiCurrent.querySelector(".tree5");
            var lLiUp = lLiCurrent.querySelector(".tree6");
            lLiDown.classList.remove("hide");
            lLiUp.classList.remove("hide");
        }
    }

    updateArrows(_parent) {
        this.showArrows(_parent);
        var lLis = _parent.querySelectorAll(":scope > li > .tree3, :scope > .tree4");
        for(var i = 0; i < lLis.length; i++) {
            var lLiCurrent = lLis[i];
            var lLiDown = lLiCurrent.querySelector(".tree5");
            var lLiUp = lLiCurrent.querySelector(".tree6");
            if(lLiCurrent.classList.contains("tree3")) {
                lLiCurrent = lLiCurrent.parentElement;
            }
            if(!lLiCurrent.nextElementSibling) {
                lLiDown.classList.add("hide");
            }
            if(!lLiCurrent.previousElementSibling) {
                lLiUp.classList.add("hide");
            }
        }
    }

    readJson(_parent) {
        var lParent = document.querySelector(_parent);
        var lLis = lParent.querySelectorAll(":scope > li > .tree3, :scope > .tree4");
        var lTreeMap = [];
        for(var i = 0; i < lLis.length; i++) {
            var lLi = lLis[i];
            if(lLi.classList.contains("tree3")) {
                console.log(sprintf("%s", lLi.dataset.value));
                var lObj = new html_tree_data(
                lTreeMap.length + 1
                , 0
                , lLi.dataset.value
                , "dir");
                lTreeMap.push(lObj);
                this.readItem(lTreeMap, lObj, lLi.nextElementSibling, "    ");
            }
            else {
                console.log(sprintf("%s", lLi.dataset.value));
                var lObj = new html_tree_data(
                lTreeMap.length + 1
                , 0
                , lLi.dataset.value
                , "file");
                lTreeMap.push(lObj);
            }
        }
        var lTreeMapObj = new html_tree_map(lTreeMap);
        return lTreeMapObj.serializeJson();
    }

    readItem(_treeMap, _obj, _parent, _shift) {
        var lLis = _parent.querySelectorAll(":scope > li > .tree3, :scope > .tree4");
        for(var i = 0; i < lLis.length; i++) {
            var lLi = lLis[i];
            if(lLi.classList.contains("tree3")) {
                console.log(sprintf("%s%s", _shift, lLi.dataset.value));
                var lObj = new html_tree_data(
                _treeMap.length + 1
                , _obj.m_index
                , lLi.dataset.value
                , "dir");
                _treeMap.push(lObj);
                this.readItem(_treeMap, lObj, lLi.nextElementSibling, _shift + "    ");
            }
            else {
                console.log(sprintf("%s%s", _shift, lLi.dataset.value));
                var lObj = new html_tree_data(
                _treeMap.length + 1
                , _obj.m_index
                , lLi.dataset.value
                , "file");
                _treeMap.push(lObj);
            }
        }
    }

    run() {
        var lData = this.readJson("#tree");
        var lAjax = new common_ajax("/callback/test/html_tree");
        lAjax.run(lData, this.onRunCB);
    }

    onRunCB(_data) {
        console.log(sprintf(_data));
    }

}

html_tree.Instance().init();
