import { writable, derived} from 'svelte/store'

// Contains the following fields:
// beam: the instance of the Beamable Web SDK, initialized in the page's cid/pid
export const Context = writable({
    beam: null
});

export const Beam = derived(Context, ($ctx) => $ctx.beam)