import { mount, unmount } from 'svelte'
import './app.css'
import App from './App.svelte'

const APP_NAMESPACE = 'edgegap_server_extensions';

window[APP_NAMESPACE] = {
  mount: (targetElement, props) => {
    return mount(App, { 
        target: targetElement, 
        props: props 
    });
  },
  unmount: (appInstance) => {
    unmount(appInstance);
  }
}
