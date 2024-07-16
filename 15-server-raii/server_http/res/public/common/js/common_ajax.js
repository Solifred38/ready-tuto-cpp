class common_ajax {
    constructor(_requestUrl) {
        this.m_requestUrl       = _requestUrl;
        this.m_requestType      = "application/json";
        this.m_responseAccept   = "text";
        this.m_requestMethod    = "post";
        this.m_requestAsync     = true;
        this.m_requestUser      = null;
        this.m_requestPassword  = null;
    }

    run(_data, _callback = null) {
        var lXhttp = new XMLHttpRequest();
        lXhttp.onreadystatechange = function() {
            if(this.readyState == 4 && this.status == 200) {
                var lResponseText   = this.responseText;
                if(_callback) _callback(lResponseText);
            }
        }

        lXhttp.open(this.m_requestMethod, this.m_requestUrl, this.m_requestAsync, this.m_requestUser, this.m_requestPassword);
        lXhttp.setRequestHeader("Content-Type", this.m_requestType);
        lXhttp.responseType = this.m_responseAccept;

        lXhttp.send(_data);
    }
}
