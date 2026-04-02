import { mount, unmount } from 'svelte'
import './app.css'
import App from './App.svelte'
import { Portal } from '@beamable/portal-toolkit'

Portal.registerExtension({
    beamId: 'edgegap_extensions',
    onMount: (container, context) => {
        return mount(App, {
            target: container,
            props: { context } });
    },
    onUnmount: instance => {
        unmount(instance);
    }
})
