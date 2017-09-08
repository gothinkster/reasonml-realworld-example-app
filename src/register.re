let component = ReasonReact.statelessComponent "Register";
let show = ReasonReact.stringToElement;

let make _children => {
  ...component,
  render: fun _self => {
    <div className="auth-page">
      <div className="container page">
        <div className="row">
    
          <div className="col-md-6 offset-md-3 col-xs-12">
            <h1 className="text-xs-center">(show "Sign up")</h1>
            <p className="text-xs-center">
              <a href="">(show "Have an account?")</a>
            </p>
    
            <ul className="error-messages">
              <li>(show "That email is already taken")</li>
            </ul>
    
            <form>
              <fieldset className="form-group">
                <input _type="text" className="form-control form-control-lg"  placeholder="Your Name" />
              </fieldset>
              <fieldset className="form-group">
                <input _type="text" className="form-control form-control-lg" placeholder="Email" />
              </fieldset>
              <fieldset className="form-group">
                <input _type="password" className="form-control form-control-lg" placeholder="Password" />
              </fieldset>
              <button className="btn btn-lg btn-primary pull-xs-right">
                (show "Sign up")
              </button>
            </form>
          </div>    
        </div>
      </div>
    </div>
  }
};