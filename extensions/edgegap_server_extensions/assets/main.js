(function() {
  "use strict";
  const DEV = false;
  var is_array = Array.isArray;
  var index_of = Array.prototype.indexOf;
  var includes = Array.prototype.includes;
  var array_from = Array.from;
  var define_property = Object.defineProperty;
  var get_descriptor = Object.getOwnPropertyDescriptor;
  var get_descriptors = Object.getOwnPropertyDescriptors;
  var object_prototype = Object.prototype;
  var array_prototype = Array.prototype;
  var get_prototype_of = Object.getPrototypeOf;
  var is_extensible = Object.isExtensible;
  const noop = () => {
  };
  function run(fn) {
    return fn();
  }
  function run_all(arr) {
    for (var i = 0; i < arr.length; i++) {
      arr[i]();
    }
  }
  function deferred() {
    var resolve;
    var reject;
    var promise = new Promise((res, rej) => {
      resolve = res;
      reject = rej;
    });
    return { promise, resolve, reject };
  }
  const DERIVED = 1 << 1;
  const EFFECT = 1 << 2;
  const RENDER_EFFECT = 1 << 3;
  const MANAGED_EFFECT = 1 << 24;
  const BLOCK_EFFECT = 1 << 4;
  const BRANCH_EFFECT = 1 << 5;
  const ROOT_EFFECT = 1 << 6;
  const BOUNDARY_EFFECT = 1 << 7;
  const CONNECTED = 1 << 9;
  const CLEAN = 1 << 10;
  const DIRTY = 1 << 11;
  const MAYBE_DIRTY = 1 << 12;
  const INERT = 1 << 13;
  const DESTROYED = 1 << 14;
  const REACTION_RAN = 1 << 15;
  const DESTROYING = 1 << 25;
  const EFFECT_TRANSPARENT = 1 << 16;
  const EAGER_EFFECT = 1 << 17;
  const HEAD_EFFECT = 1 << 18;
  const EFFECT_PRESERVED = 1 << 19;
  const USER_EFFECT = 1 << 20;
  const EFFECT_OFFSCREEN = 1 << 25;
  const WAS_MARKED = 1 << 16;
  const REACTION_IS_UPDATING = 1 << 21;
  const ASYNC = 1 << 22;
  const ERROR_VALUE = 1 << 23;
  const STATE_SYMBOL = /* @__PURE__ */ Symbol("$state");
  const LEGACY_PROPS = /* @__PURE__ */ Symbol("legacy props");
  const LOADING_ATTR_SYMBOL = /* @__PURE__ */ Symbol("");
  const STALE_REACTION = new class StaleReactionError extends Error {
    name = "StaleReactionError";
    message = "The reaction that called `getAbortSignal()` was re-run or destroyed";
  }();
  function lifecycle_outside_component(name) {
    {
      throw new Error(`https://svelte.dev/e/lifecycle_outside_component`);
    }
  }
  function async_derived_orphan() {
    {
      throw new Error(`https://svelte.dev/e/async_derived_orphan`);
    }
  }
  function each_key_duplicate(a, b, value) {
    {
      throw new Error(`https://svelte.dev/e/each_key_duplicate`);
    }
  }
  function effect_in_teardown(rune) {
    {
      throw new Error(`https://svelte.dev/e/effect_in_teardown`);
    }
  }
  function effect_in_unowned_derived() {
    {
      throw new Error(`https://svelte.dev/e/effect_in_unowned_derived`);
    }
  }
  function effect_orphan(rune) {
    {
      throw new Error(`https://svelte.dev/e/effect_orphan`);
    }
  }
  function effect_update_depth_exceeded() {
    {
      throw new Error(`https://svelte.dev/e/effect_update_depth_exceeded`);
    }
  }
  function state_descriptors_fixed() {
    {
      throw new Error(`https://svelte.dev/e/state_descriptors_fixed`);
    }
  }
  function state_prototype_fixed() {
    {
      throw new Error(`https://svelte.dev/e/state_prototype_fixed`);
    }
  }
  function state_unsafe_mutation() {
    {
      throw new Error(`https://svelte.dev/e/state_unsafe_mutation`);
    }
  }
  function svelte_boundary_reset_onerror() {
    {
      throw new Error(`https://svelte.dev/e/svelte_boundary_reset_onerror`);
    }
  }
  const EACH_ITEM_REACTIVE = 1;
  const EACH_INDEX_REACTIVE = 1 << 1;
  const EACH_ITEM_IMMUTABLE = 1 << 4;
  const PROPS_IS_RUNES = 1 << 1;
  const PROPS_IS_UPDATED = 1 << 2;
  const PROPS_IS_BINDABLE = 1 << 3;
  const TEMPLATE_FRAGMENT = 1;
  const TEMPLATE_USE_IMPORT_NODE = 1 << 1;
  const UNINITIALIZED = /* @__PURE__ */ Symbol();
  const NAMESPACE_HTML = "http://www.w3.org/1999/xhtml";
  function svelte_boundary_reset_noop() {
    {
      console.warn(`https://svelte.dev/e/svelte_boundary_reset_noop`);
    }
  }
  function equals(value) {
    return value === this.v;
  }
  function safe_not_equal(a, b) {
    return a != a ? b == b : a !== b || a !== null && typeof a === "object" || typeof a === "function";
  }
  function safe_equals(value) {
    return !safe_not_equal(value, this.v);
  }
  let legacy_mode_flag = false;
  let tracing_mode_flag = false;
  function enable_legacy_mode_flag() {
    legacy_mode_flag = true;
  }
  let component_context = null;
  function set_component_context(context) {
    component_context = context;
  }
  function push(props, runes = false, fn) {
    component_context = {
      p: component_context,
      i: false,
      c: null,
      e: null,
      s: props,
      x: null,
      r: (
        /** @type {Effect} */
        active_effect
      ),
      l: legacy_mode_flag && !runes ? { s: null, u: null, $: [] } : null
    };
  }
  function pop(component) {
    var context = (
      /** @type {ComponentContext} */
      component_context
    );
    var effects = context.e;
    if (effects !== null) {
      context.e = null;
      for (var fn of effects) {
        create_user_effect(fn);
      }
    }
    context.i = true;
    component_context = context.p;
    return (
      /** @type {T} */
      {}
    );
  }
  function is_runes() {
    return !legacy_mode_flag || component_context !== null && component_context.l === null;
  }
  let micro_tasks = [];
  function run_micro_tasks() {
    var tasks = micro_tasks;
    micro_tasks = [];
    run_all(tasks);
  }
  function queue_micro_task(fn) {
    if (micro_tasks.length === 0 && true) {
      var tasks = micro_tasks;
      queueMicrotask(() => {
        if (tasks === micro_tasks) run_micro_tasks();
      });
    }
    micro_tasks.push(fn);
  }
  function handle_error(error) {
    var effect = active_effect;
    if (effect === null) {
      active_reaction.f |= ERROR_VALUE;
      return error;
    }
    if ((effect.f & REACTION_RAN) === 0 && (effect.f & EFFECT) === 0) {
      throw error;
    }
    invoke_error_boundary(error, effect);
  }
  function invoke_error_boundary(error, effect) {
    while (effect !== null) {
      if ((effect.f & BOUNDARY_EFFECT) !== 0) {
        if ((effect.f & REACTION_RAN) === 0) {
          throw error;
        }
        try {
          effect.b.error(error);
          return;
        } catch (e) {
          error = e;
        }
      }
      effect = effect.parent;
    }
    throw error;
  }
  const STATUS_MASK = -7169;
  function set_signal_status(signal, status) {
    signal.f = signal.f & STATUS_MASK | status;
  }
  function update_derived_status(derived2) {
    if ((derived2.f & CONNECTED) !== 0 || derived2.deps === null) {
      set_signal_status(derived2, CLEAN);
    } else {
      set_signal_status(derived2, MAYBE_DIRTY);
    }
  }
  function clear_marked(deps) {
    if (deps === null) return;
    for (const dep of deps) {
      if ((dep.f & DERIVED) === 0 || (dep.f & WAS_MARKED) === 0) {
        continue;
      }
      dep.f ^= WAS_MARKED;
      clear_marked(
        /** @type {Derived} */
        dep.deps
      );
    }
  }
  function defer_effect(effect, dirty_effects, maybe_dirty_effects) {
    if ((effect.f & DIRTY) !== 0) {
      dirty_effects.add(effect);
    } else if ((effect.f & MAYBE_DIRTY) !== 0) {
      maybe_dirty_effects.add(effect);
    }
    clear_marked(effect.deps);
    set_signal_status(effect, CLEAN);
  }
  function subscribe_to_store(store, run2, invalidate) {
    if (store == null) {
      run2(void 0);
      if (invalidate) invalidate(void 0);
      return noop;
    }
    const unsub = untrack(
      () => store.subscribe(
        run2,
        // @ts-expect-error
        invalidate
      )
    );
    return unsub.unsubscribe ? () => unsub.unsubscribe() : unsub;
  }
  const subscriber_queue = [];
  function readable(value, start) {
    return {
      subscribe: writable(value, start).subscribe
    };
  }
  function writable(value, start = noop) {
    let stop = null;
    const subscribers = /* @__PURE__ */ new Set();
    function set2(new_value) {
      if (safe_not_equal(value, new_value)) {
        value = new_value;
        if (stop) {
          const run_queue = !subscriber_queue.length;
          for (const subscriber of subscribers) {
            subscriber[1]();
            subscriber_queue.push(subscriber, value);
          }
          if (run_queue) {
            for (let i = 0; i < subscriber_queue.length; i += 2) {
              subscriber_queue[i][0](subscriber_queue[i + 1]);
            }
            subscriber_queue.length = 0;
          }
        }
      }
    }
    function update(fn) {
      set2(fn(
        /** @type {T} */
        value
      ));
    }
    function subscribe(run2, invalidate = noop) {
      const subscriber = [run2, invalidate];
      subscribers.add(subscriber);
      if (subscribers.size === 1) {
        stop = start(set2, update) || noop;
      }
      run2(
        /** @type {T} */
        value
      );
      return () => {
        subscribers.delete(subscriber);
        if (subscribers.size === 0 && stop) {
          stop();
          stop = null;
        }
      };
    }
    return { set: set2, update, subscribe };
  }
  function derived$1(stores, fn, initial_value) {
    const single = !Array.isArray(stores);
    const stores_array = single ? [stores] : stores;
    if (!stores_array.every(Boolean)) {
      throw new Error("derived() expects stores as input, got a falsy value");
    }
    const auto = fn.length < 2;
    return readable(initial_value, (set2, update) => {
      let started = false;
      const values = [];
      let pending = 0;
      let cleanup = noop;
      const sync = () => {
        if (pending) {
          return;
        }
        cleanup();
        const result = fn(single ? values[0] : values, set2, update);
        if (auto) {
          set2(result);
        } else {
          cleanup = typeof result === "function" ? result : noop;
        }
      };
      const unsubscribers = stores_array.map(
        (store, i) => subscribe_to_store(
          store,
          (value) => {
            values[i] = value;
            pending &= ~(1 << i);
            if (started) {
              sync();
            }
          },
          () => {
            pending |= 1 << i;
          }
        )
      );
      started = true;
      sync();
      return function stop() {
        run_all(unsubscribers);
        cleanup();
        started = false;
      };
    });
  }
  let is_store_binding = false;
  function capture_store_binding(fn) {
    var previous_is_store_binding = is_store_binding;
    try {
      is_store_binding = false;
      return [fn(), is_store_binding];
    } finally {
      is_store_binding = previous_is_store_binding;
    }
  }
  const batches = /* @__PURE__ */ new Set();
  let current_batch = null;
  let batch_values = null;
  let last_scheduled_effect = null;
  let is_processing = false;
  let collected_effects = null;
  let legacy_updates = null;
  var flush_count = 0;
  let uid = 1;
  class Batch {
    id = uid++;
    /**
     * The current values of any signals that are updated in this batch.
     * Tuple format: [value, is_derived] (note: is_derived is false for deriveds, too, if they were overridden via assignment)
     * They keys of this map are identical to `this.#previous`
     * @type {Map<Value, [any, boolean]>}
     */
    current = /* @__PURE__ */ new Map();
    /**
     * The values of any signals (sources and deriveds) that are updated in this batch _before_ those updates took place.
     * They keys of this map are identical to `this.#current`
     * @type {Map<Value, any>}
     */
    previous = /* @__PURE__ */ new Map();
    /**
     * When the batch is committed (and the DOM is updated), we need to remove old branches
     * and append new ones by calling the functions added inside (if/each/key/etc) blocks
     * @type {Set<(batch: Batch) => void>}
     */
    #commit_callbacks = /* @__PURE__ */ new Set();
    /**
     * If a fork is discarded, we need to destroy any effects that are no longer needed
     * @type {Set<(batch: Batch) => void>}
     */
    #discard_callbacks = /* @__PURE__ */ new Set();
    /**
     * Async effects that are currently in flight
     * @type {Map<Effect, number>}
     */
    #pending = /* @__PURE__ */ new Map();
    /**
     * Async effects that are currently in flight, _not_ inside a pending boundary
     * @type {Map<Effect, number>}
     */
    #blocking_pending = /* @__PURE__ */ new Map();
    /**
     * A deferred that resolves when the batch is committed, used with `settled()`
     * TODO replace with Promise.withResolvers once supported widely enough
     * @type {{ promise: Promise<void>, resolve: (value?: any) => void, reject: (reason: unknown) => void } | null}
     */
    #deferred = null;
    /**
     * The root effects that need to be flushed
     * @type {Effect[]}
     */
    #roots = [];
    /**
     * Effects created while this batch was active.
     * @type {Effect[]}
     */
    #new_effects = [];
    /**
     * Deferred effects (which run after async work has completed) that are DIRTY
     * @type {Set<Effect>}
     */
    #dirty_effects = /* @__PURE__ */ new Set();
    /**
     * Deferred effects that are MAYBE_DIRTY
     * @type {Set<Effect>}
     */
    #maybe_dirty_effects = /* @__PURE__ */ new Set();
    /**
     * A map of branches that still exist, but will be destroyed when this batch
     * is committed — we skip over these during `process`.
     * The value contains child effects that were dirty/maybe_dirty before being reset,
     * so they can be rescheduled if the branch survives.
     * @type {Map<Effect, { d: Effect[], m: Effect[] }>}
     */
    #skipped_branches = /* @__PURE__ */ new Map();
    is_fork = false;
    #decrement_queued = false;
    /** @type {Set<Batch>} */
    #blockers = /* @__PURE__ */ new Set();
    #is_deferred() {
      return this.is_fork || this.#blocking_pending.size > 0;
    }
    #is_blocked() {
      for (const batch of this.#blockers) {
        for (const effect of batch.#blocking_pending.keys()) {
          var skipped = false;
          var e = effect;
          while (e.parent !== null) {
            if (this.#skipped_branches.has(e)) {
              skipped = true;
              break;
            }
            e = e.parent;
          }
          if (!skipped) {
            return true;
          }
        }
      }
      return false;
    }
    /**
     * Add an effect to the #skipped_branches map and reset its children
     * @param {Effect} effect
     */
    skip_effect(effect) {
      if (!this.#skipped_branches.has(effect)) {
        this.#skipped_branches.set(effect, { d: [], m: [] });
      }
    }
    /**
     * Remove an effect from the #skipped_branches map and reschedule
     * any tracked dirty/maybe_dirty child effects
     * @param {Effect} effect
     */
    unskip_effect(effect) {
      var tracked = this.#skipped_branches.get(effect);
      if (tracked) {
        this.#skipped_branches.delete(effect);
        for (var e of tracked.d) {
          set_signal_status(e, DIRTY);
          this.schedule(e);
        }
        for (e of tracked.m) {
          set_signal_status(e, MAYBE_DIRTY);
          this.schedule(e);
        }
      }
    }
    #process() {
      if (flush_count++ > 1e3) {
        batches.delete(this);
        infinite_loop_guard();
      }
      if (!this.#is_deferred()) {
        for (const e of this.#dirty_effects) {
          this.#maybe_dirty_effects.delete(e);
          set_signal_status(e, DIRTY);
          this.schedule(e);
        }
        for (const e of this.#maybe_dirty_effects) {
          set_signal_status(e, MAYBE_DIRTY);
          this.schedule(e);
        }
      }
      const roots = this.#roots;
      this.#roots = [];
      this.apply();
      var effects = collected_effects = [];
      var render_effects = [];
      var updates = legacy_updates = [];
      for (const root2 of roots) {
        try {
          this.#traverse(root2, effects, render_effects);
        } catch (e) {
          reset_all(root2);
          throw e;
        }
      }
      current_batch = null;
      if (updates.length > 0) {
        var batch = Batch.ensure();
        for (const e of updates) {
          batch.schedule(e);
        }
      }
      collected_effects = null;
      legacy_updates = null;
      if (this.#is_deferred() || this.#is_blocked()) {
        this.#defer_effects(render_effects);
        this.#defer_effects(effects);
        for (const [e, t] of this.#skipped_branches) {
          reset_branch(e, t);
        }
      } else {
        if (this.#pending.size === 0) {
          batches.delete(this);
        }
        this.#dirty_effects.clear();
        this.#maybe_dirty_effects.clear();
        for (const fn of this.#commit_callbacks) fn(this);
        this.#commit_callbacks.clear();
        flush_queued_effects(render_effects);
        flush_queued_effects(effects);
        this.#deferred?.resolve();
      }
      var next_batch = (
        /** @type {Batch | null} */
        /** @type {unknown} */
        current_batch
      );
      if (this.#roots.length > 0) {
        const batch2 = next_batch ??= this;
        batch2.#roots.push(...this.#roots.filter((r) => !batch2.#roots.includes(r)));
      }
      if (next_batch !== null) {
        batches.add(next_batch);
        next_batch.#process();
      }
      if (!batches.has(this)) {
        this.#commit();
      }
    }
    /**
     * Traverse the effect tree, executing effects or stashing
     * them for later execution as appropriate
     * @param {Effect} root
     * @param {Effect[]} effects
     * @param {Effect[]} render_effects
     */
    #traverse(root2, effects, render_effects) {
      root2.f ^= CLEAN;
      var effect = root2.first;
      while (effect !== null) {
        var flags2 = effect.f;
        var is_branch = (flags2 & (BRANCH_EFFECT | ROOT_EFFECT)) !== 0;
        var is_skippable_branch = is_branch && (flags2 & CLEAN) !== 0;
        var skip = is_skippable_branch || (flags2 & INERT) !== 0 || this.#skipped_branches.has(effect);
        if (!skip && effect.fn !== null) {
          if (is_branch) {
            effect.f ^= CLEAN;
          } else if ((flags2 & EFFECT) !== 0) {
            effects.push(effect);
          } else if (is_dirty(effect)) {
            if ((flags2 & BLOCK_EFFECT) !== 0) this.#maybe_dirty_effects.add(effect);
            update_effect(effect);
          }
          var child2 = effect.first;
          if (child2 !== null) {
            effect = child2;
            continue;
          }
        }
        while (effect !== null) {
          var next = effect.next;
          if (next !== null) {
            effect = next;
            break;
          }
          effect = effect.parent;
        }
      }
    }
    /**
     * @param {Effect[]} effects
     */
    #defer_effects(effects) {
      for (var i = 0; i < effects.length; i += 1) {
        defer_effect(effects[i], this.#dirty_effects, this.#maybe_dirty_effects);
      }
    }
    /**
     * Associate a change to a given source with the current
     * batch, noting its previous and current values
     * @param {Value} source
     * @param {any} old_value
     * @param {boolean} [is_derived]
     */
    capture(source2, old_value, is_derived = false) {
      if (old_value !== UNINITIALIZED && !this.previous.has(source2)) {
        this.previous.set(source2, old_value);
      }
      if ((source2.f & ERROR_VALUE) === 0) {
        this.current.set(source2, [source2.v, is_derived]);
        batch_values?.set(source2, source2.v);
      }
    }
    activate() {
      current_batch = this;
    }
    deactivate() {
      current_batch = null;
      batch_values = null;
    }
    flush() {
      try {
        is_processing = true;
        current_batch = this;
        this.#process();
      } finally {
        flush_count = 0;
        last_scheduled_effect = null;
        collected_effects = null;
        legacy_updates = null;
        is_processing = false;
        current_batch = null;
        batch_values = null;
        old_values.clear();
      }
    }
    discard() {
      for (const fn of this.#discard_callbacks) fn(this);
      this.#discard_callbacks.clear();
      batches.delete(this);
    }
    /**
     * @param {Effect} effect
     */
    register_created_effect(effect) {
      this.#new_effects.push(effect);
    }
    #commit() {
      for (const batch of batches) {
        var is_earlier = batch.id < this.id;
        var sources = [];
        for (const [source3, [value, is_derived]] of this.current) {
          if (batch.current.has(source3)) {
            var batch_value = (
              /** @type {[any, boolean]} */
              batch.current.get(source3)[0]
            );
            if (is_earlier && value !== batch_value) {
              batch.current.set(source3, [value, is_derived]);
            } else {
              continue;
            }
          }
          sources.push(source3);
        }
        var others = [...batch.current.keys()].filter((s) => !this.current.has(s));
        if (others.length === 0) {
          if (is_earlier) {
            batch.discard();
          }
        } else if (sources.length > 0) {
          batch.activate();
          var marked = /* @__PURE__ */ new Set();
          var checked = /* @__PURE__ */ new Map();
          for (var source2 of sources) {
            mark_effects(source2, others, marked, checked);
          }
          checked = /* @__PURE__ */ new Map();
          var current_unequal = [...batch.current.keys()].filter(
            (c) => this.current.has(c) ? (
              /** @type {[any, boolean]} */
              this.current.get(c)[0] !== c
            ) : true
          );
          for (const effect of this.#new_effects) {
            if ((effect.f & (DESTROYED | INERT | EAGER_EFFECT)) === 0 && depends_on(effect, current_unequal, checked)) {
              if ((effect.f & (ASYNC | BLOCK_EFFECT)) !== 0) {
                set_signal_status(effect, DIRTY);
                batch.schedule(effect);
              } else {
                batch.#dirty_effects.add(effect);
              }
            }
          }
          if (batch.#roots.length > 0) {
            batch.apply();
            for (var root2 of batch.#roots) {
              batch.#traverse(root2, [], []);
            }
            batch.#roots = [];
          }
          batch.deactivate();
        }
      }
      for (const batch of batches) {
        if (batch.#blockers.has(this)) {
          batch.#blockers.delete(this);
          if (batch.#blockers.size === 0 && !batch.#is_deferred()) {
            batch.activate();
            batch.#process();
          }
        }
      }
    }
    /**
     * @param {boolean} blocking
     * @param {Effect} effect
     */
    increment(blocking, effect) {
      let pending_count = this.#pending.get(effect) ?? 0;
      this.#pending.set(effect, pending_count + 1);
      if (blocking) {
        let blocking_pending_count = this.#blocking_pending.get(effect) ?? 0;
        this.#blocking_pending.set(effect, blocking_pending_count + 1);
      }
    }
    /**
     * @param {boolean} blocking
     * @param {Effect} effect
     * @param {boolean} skip - whether to skip updates (because this is triggered by a stale reaction)
     */
    decrement(blocking, effect, skip) {
      let pending_count = this.#pending.get(effect) ?? 0;
      if (pending_count === 1) {
        this.#pending.delete(effect);
      } else {
        this.#pending.set(effect, pending_count - 1);
      }
      if (blocking) {
        let blocking_pending_count = this.#blocking_pending.get(effect) ?? 0;
        if (blocking_pending_count === 1) {
          this.#blocking_pending.delete(effect);
        } else {
          this.#blocking_pending.set(effect, blocking_pending_count - 1);
        }
      }
      if (this.#decrement_queued || skip) return;
      this.#decrement_queued = true;
      queue_micro_task(() => {
        this.#decrement_queued = false;
        this.flush();
      });
    }
    /**
     * @param {Set<Effect>} dirty_effects
     * @param {Set<Effect>} maybe_dirty_effects
     */
    transfer_effects(dirty_effects, maybe_dirty_effects) {
      for (const e of dirty_effects) {
        this.#dirty_effects.add(e);
      }
      for (const e of maybe_dirty_effects) {
        this.#maybe_dirty_effects.add(e);
      }
      dirty_effects.clear();
      maybe_dirty_effects.clear();
    }
    /** @param {(batch: Batch) => void} fn */
    oncommit(fn) {
      this.#commit_callbacks.add(fn);
    }
    /** @param {(batch: Batch) => void} fn */
    ondiscard(fn) {
      this.#discard_callbacks.add(fn);
    }
    settled() {
      return (this.#deferred ??= deferred()).promise;
    }
    static ensure() {
      if (current_batch === null) {
        const batch = current_batch = new Batch();
        if (!is_processing) {
          batches.add(current_batch);
          {
            queue_micro_task(() => {
              if (current_batch !== batch) {
                return;
              }
              batch.flush();
            });
          }
        }
      }
      return current_batch;
    }
    apply() {
      {
        batch_values = null;
        return;
      }
    }
    /**
     *
     * @param {Effect} effect
     */
    schedule(effect) {
      last_scheduled_effect = effect;
      if (effect.b?.is_pending && (effect.f & (EFFECT | RENDER_EFFECT | MANAGED_EFFECT)) !== 0 && (effect.f & REACTION_RAN) === 0) {
        effect.b.defer_effect(effect);
        return;
      }
      var e = effect;
      while (e.parent !== null) {
        e = e.parent;
        var flags2 = e.f;
        if (collected_effects !== null && e === active_effect) {
          if ((active_reaction === null || (active_reaction.f & DERIVED) === 0) && true) {
            return;
          }
        }
        if ((flags2 & (ROOT_EFFECT | BRANCH_EFFECT)) !== 0) {
          if ((flags2 & CLEAN) === 0) {
            return;
          }
          e.f ^= CLEAN;
        }
      }
      this.#roots.push(e);
    }
  }
  function infinite_loop_guard() {
    try {
      effect_update_depth_exceeded();
    } catch (error) {
      invoke_error_boundary(error, last_scheduled_effect);
    }
  }
  let eager_block_effects = null;
  function flush_queued_effects(effects) {
    var length = effects.length;
    if (length === 0) return;
    var i = 0;
    while (i < length) {
      var effect = effects[i++];
      if ((effect.f & (DESTROYED | INERT)) === 0 && is_dirty(effect)) {
        eager_block_effects = /* @__PURE__ */ new Set();
        update_effect(effect);
        if (effect.deps === null && effect.first === null && effect.nodes === null && effect.teardown === null && effect.ac === null) {
          unlink_effect(effect);
        }
        if (eager_block_effects?.size > 0) {
          old_values.clear();
          for (const e of eager_block_effects) {
            if ((e.f & (DESTROYED | INERT)) !== 0) continue;
            const ordered_effects = [e];
            let ancestor = e.parent;
            while (ancestor !== null) {
              if (eager_block_effects.has(ancestor)) {
                eager_block_effects.delete(ancestor);
                ordered_effects.push(ancestor);
              }
              ancestor = ancestor.parent;
            }
            for (let j = ordered_effects.length - 1; j >= 0; j--) {
              const e2 = ordered_effects[j];
              if ((e2.f & (DESTROYED | INERT)) !== 0) continue;
              update_effect(e2);
            }
          }
          eager_block_effects.clear();
        }
      }
    }
    eager_block_effects = null;
  }
  function mark_effects(value, sources, marked, checked) {
    if (marked.has(value)) return;
    marked.add(value);
    if (value.reactions !== null) {
      for (const reaction of value.reactions) {
        const flags2 = reaction.f;
        if ((flags2 & DERIVED) !== 0) {
          mark_effects(
            /** @type {Derived} */
            reaction,
            sources,
            marked,
            checked
          );
        } else if ((flags2 & (ASYNC | BLOCK_EFFECT)) !== 0 && (flags2 & DIRTY) === 0 && depends_on(reaction, sources, checked)) {
          set_signal_status(reaction, DIRTY);
          schedule_effect(
            /** @type {Effect} */
            reaction
          );
        }
      }
    }
  }
  function depends_on(reaction, sources, checked) {
    const depends = checked.get(reaction);
    if (depends !== void 0) return depends;
    if (reaction.deps !== null) {
      for (const dep of reaction.deps) {
        if (includes.call(sources, dep)) {
          return true;
        }
        if ((dep.f & DERIVED) !== 0 && depends_on(
          /** @type {Derived} */
          dep,
          sources,
          checked
        )) {
          checked.set(
            /** @type {Derived} */
            dep,
            true
          );
          return true;
        }
      }
    }
    checked.set(reaction, false);
    return false;
  }
  function schedule_effect(effect) {
    current_batch.schedule(effect);
  }
  function reset_branch(effect, tracked) {
    if ((effect.f & BRANCH_EFFECT) !== 0 && (effect.f & CLEAN) !== 0) {
      return;
    }
    if ((effect.f & DIRTY) !== 0) {
      tracked.d.push(effect);
    } else if ((effect.f & MAYBE_DIRTY) !== 0) {
      tracked.m.push(effect);
    }
    set_signal_status(effect, CLEAN);
    var e = effect.first;
    while (e !== null) {
      reset_branch(e, tracked);
      e = e.next;
    }
  }
  function reset_all(effect) {
    set_signal_status(effect, CLEAN);
    var e = effect.first;
    while (e !== null) {
      reset_all(e);
      e = e.next;
    }
  }
  function createSubscriber(start) {
    let subscribers = 0;
    let version = source(0);
    let stop;
    return () => {
      if (effect_tracking()) {
        get(version);
        render_effect(() => {
          if (subscribers === 0) {
            stop = untrack(() => start(() => increment(version)));
          }
          subscribers += 1;
          return () => {
            queue_micro_task(() => {
              subscribers -= 1;
              if (subscribers === 0) {
                stop?.();
                stop = void 0;
                increment(version);
              }
            });
          };
        });
      }
    };
  }
  var flags = EFFECT_TRANSPARENT | EFFECT_PRESERVED;
  function boundary(node, props, children, transform_error) {
    new Boundary(node, props, children, transform_error);
  }
  class Boundary {
    /** @type {Boundary | null} */
    parent;
    is_pending = false;
    /**
     * API-level transformError transform function. Transforms errors before they reach the `failed` snippet.
     * Inherited from parent boundary, or defaults to identity.
     * @type {(error: unknown) => unknown}
     */
    transform_error;
    /** @type {TemplateNode} */
    #anchor;
    /** @type {TemplateNode | null} */
    #hydrate_open = null;
    /** @type {BoundaryProps} */
    #props;
    /** @type {((anchor: Node) => void)} */
    #children;
    /** @type {Effect} */
    #effect;
    /** @type {Effect | null} */
    #main_effect = null;
    /** @type {Effect | null} */
    #pending_effect = null;
    /** @type {Effect | null} */
    #failed_effect = null;
    /** @type {DocumentFragment | null} */
    #offscreen_fragment = null;
    #local_pending_count = 0;
    #pending_count = 0;
    #pending_count_update_queued = false;
    /** @type {Set<Effect>} */
    #dirty_effects = /* @__PURE__ */ new Set();
    /** @type {Set<Effect>} */
    #maybe_dirty_effects = /* @__PURE__ */ new Set();
    /**
     * A source containing the number of pending async deriveds/expressions.
     * Only created if `$effect.pending()` is used inside the boundary,
     * otherwise updating the source results in needless `Batch.ensure()`
     * calls followed by no-op flushes
     * @type {Source<number> | null}
     */
    #effect_pending = null;
    #effect_pending_subscriber = createSubscriber(() => {
      this.#effect_pending = source(this.#local_pending_count);
      return () => {
        this.#effect_pending = null;
      };
    });
    /**
     * @param {TemplateNode} node
     * @param {BoundaryProps} props
     * @param {((anchor: Node) => void)} children
     * @param {((error: unknown) => unknown) | undefined} [transform_error]
     */
    constructor(node, props, children, transform_error) {
      this.#anchor = node;
      this.#props = props;
      this.#children = (anchor) => {
        var effect = (
          /** @type {Effect} */
          active_effect
        );
        effect.b = this;
        effect.f |= BOUNDARY_EFFECT;
        children(anchor);
      };
      this.parent = /** @type {Effect} */
      active_effect.b;
      this.transform_error = transform_error ?? this.parent?.transform_error ?? ((e) => e);
      this.#effect = block(() => {
        {
          this.#render();
        }
      }, flags);
    }
    #hydrate_resolved_content() {
      try {
        this.#main_effect = branch(() => this.#children(this.#anchor));
      } catch (error) {
        this.error(error);
      }
    }
    /**
     * @param {unknown} error The deserialized error from the server's hydration comment
     */
    #hydrate_failed_content(error) {
      const failed = this.#props.failed;
      if (!failed) return;
      this.#failed_effect = branch(() => {
        failed(
          this.#anchor,
          () => error,
          () => () => {
          }
        );
      });
    }
    #hydrate_pending_content() {
      const pending = this.#props.pending;
      if (!pending) return;
      this.is_pending = true;
      this.#pending_effect = branch(() => pending(this.#anchor));
      queue_micro_task(() => {
        var fragment = this.#offscreen_fragment = document.createDocumentFragment();
        var anchor = create_text();
        fragment.append(anchor);
        this.#main_effect = this.#run(() => {
          return branch(() => this.#children(anchor));
        });
        if (this.#pending_count === 0) {
          this.#anchor.before(fragment);
          this.#offscreen_fragment = null;
          pause_effect(
            /** @type {Effect} */
            this.#pending_effect,
            () => {
              this.#pending_effect = null;
            }
          );
          this.#resolve(
            /** @type {Batch} */
            current_batch
          );
        }
      });
    }
    #render() {
      try {
        this.is_pending = this.has_pending_snippet();
        this.#pending_count = 0;
        this.#local_pending_count = 0;
        this.#main_effect = branch(() => {
          this.#children(this.#anchor);
        });
        if (this.#pending_count > 0) {
          var fragment = this.#offscreen_fragment = document.createDocumentFragment();
          move_effect(this.#main_effect, fragment);
          const pending = (
            /** @type {(anchor: Node) => void} */
            this.#props.pending
          );
          this.#pending_effect = branch(() => pending(this.#anchor));
        } else {
          this.#resolve(
            /** @type {Batch} */
            current_batch
          );
        }
      } catch (error) {
        this.error(error);
      }
    }
    /**
     * @param {Batch} batch
     */
    #resolve(batch) {
      this.is_pending = false;
      batch.transfer_effects(this.#dirty_effects, this.#maybe_dirty_effects);
    }
    /**
     * Defer an effect inside a pending boundary until the boundary resolves
     * @param {Effect} effect
     */
    defer_effect(effect) {
      defer_effect(effect, this.#dirty_effects, this.#maybe_dirty_effects);
    }
    /**
     * Returns `false` if the effect exists inside a boundary whose pending snippet is shown
     * @returns {boolean}
     */
    is_rendered() {
      return !this.is_pending && (!this.parent || this.parent.is_rendered());
    }
    has_pending_snippet() {
      return !!this.#props.pending;
    }
    /**
     * @template T
     * @param {() => T} fn
     */
    #run(fn) {
      var previous_effect = active_effect;
      var previous_reaction = active_reaction;
      var previous_ctx = component_context;
      set_active_effect(this.#effect);
      set_active_reaction(this.#effect);
      set_component_context(this.#effect.ctx);
      try {
        Batch.ensure();
        return fn();
      } catch (e) {
        handle_error(e);
        return null;
      } finally {
        set_active_effect(previous_effect);
        set_active_reaction(previous_reaction);
        set_component_context(previous_ctx);
      }
    }
    /**
     * Updates the pending count associated with the currently visible pending snippet,
     * if any, such that we can replace the snippet with content once work is done
     * @param {1 | -1} d
     * @param {Batch} batch
     */
    #update_pending_count(d, batch) {
      if (!this.has_pending_snippet()) {
        if (this.parent) {
          this.parent.#update_pending_count(d, batch);
        }
        return;
      }
      this.#pending_count += d;
      if (this.#pending_count === 0) {
        this.#resolve(batch);
        if (this.#pending_effect) {
          pause_effect(this.#pending_effect, () => {
            this.#pending_effect = null;
          });
        }
        if (this.#offscreen_fragment) {
          this.#anchor.before(this.#offscreen_fragment);
          this.#offscreen_fragment = null;
        }
      }
    }
    /**
     * Update the source that powers `$effect.pending()` inside this boundary,
     * and controls when the current `pending` snippet (if any) is removed.
     * Do not call from inside the class
     * @param {1 | -1} d
     * @param {Batch} batch
     */
    update_pending_count(d, batch) {
      this.#update_pending_count(d, batch);
      this.#local_pending_count += d;
      if (!this.#effect_pending || this.#pending_count_update_queued) return;
      this.#pending_count_update_queued = true;
      queue_micro_task(() => {
        this.#pending_count_update_queued = false;
        if (this.#effect_pending) {
          internal_set(this.#effect_pending, this.#local_pending_count);
        }
      });
    }
    get_effect_pending() {
      this.#effect_pending_subscriber();
      return get(
        /** @type {Source<number>} */
        this.#effect_pending
      );
    }
    /** @param {unknown} error */
    error(error) {
      var onerror = this.#props.onerror;
      let failed = this.#props.failed;
      if (!onerror && !failed) {
        throw error;
      }
      if (this.#main_effect) {
        destroy_effect(this.#main_effect);
        this.#main_effect = null;
      }
      if (this.#pending_effect) {
        destroy_effect(this.#pending_effect);
        this.#pending_effect = null;
      }
      if (this.#failed_effect) {
        destroy_effect(this.#failed_effect);
        this.#failed_effect = null;
      }
      var did_reset = false;
      var calling_on_error = false;
      const reset = () => {
        if (did_reset) {
          svelte_boundary_reset_noop();
          return;
        }
        did_reset = true;
        if (calling_on_error) {
          svelte_boundary_reset_onerror();
        }
        if (this.#failed_effect !== null) {
          pause_effect(this.#failed_effect, () => {
            this.#failed_effect = null;
          });
        }
        this.#run(() => {
          this.#render();
        });
      };
      const handle_error_result = (transformed_error) => {
        try {
          calling_on_error = true;
          onerror?.(transformed_error, reset);
          calling_on_error = false;
        } catch (error2) {
          invoke_error_boundary(error2, this.#effect && this.#effect.parent);
        }
        if (failed) {
          this.#failed_effect = this.#run(() => {
            try {
              return branch(() => {
                var effect = (
                  /** @type {Effect} */
                  active_effect
                );
                effect.b = this;
                effect.f |= BOUNDARY_EFFECT;
                failed(
                  this.#anchor,
                  () => transformed_error,
                  () => reset
                );
              });
            } catch (error2) {
              invoke_error_boundary(
                error2,
                /** @type {Effect} */
                this.#effect.parent
              );
              return null;
            }
          });
        }
      };
      queue_micro_task(() => {
        var result;
        try {
          result = this.transform_error(error);
        } catch (e) {
          invoke_error_boundary(e, this.#effect && this.#effect.parent);
          return;
        }
        if (result !== null && typeof result === "object" && typeof /** @type {any} */
        result.then === "function") {
          result.then(
            handle_error_result,
            /** @param {unknown} e */
            (e) => invoke_error_boundary(e, this.#effect && this.#effect.parent)
          );
        } else {
          handle_error_result(result);
        }
      });
    }
  }
  function flatten(blockers, sync, async, fn) {
    const d = is_runes() ? derived : derived_safe_equal;
    var pending = blockers.filter((b) => !b.settled);
    if (async.length === 0 && pending.length === 0) {
      fn(sync.map(d));
      return;
    }
    var parent = (
      /** @type {Effect} */
      active_effect
    );
    var restore = capture();
    var blocker_promise = pending.length === 1 ? pending[0].promise : pending.length > 1 ? Promise.all(pending.map((b) => b.promise)) : null;
    function finish(values) {
      restore();
      try {
        fn(values);
      } catch (error) {
        if ((parent.f & DESTROYED) === 0) {
          invoke_error_boundary(error, parent);
        }
      }
      unset_context();
    }
    if (async.length === 0) {
      blocker_promise.then(() => finish(sync.map(d)));
      return;
    }
    var decrement_pending = increment_pending();
    function run2() {
      Promise.all(async.map((expression) => /* @__PURE__ */ async_derived(expression))).then((result) => finish([...sync.map(d), ...result])).catch((error) => invoke_error_boundary(error, parent)).finally(() => decrement_pending());
    }
    if (blocker_promise) {
      blocker_promise.then(() => {
        restore();
        run2();
        unset_context();
      });
    } else {
      run2();
    }
  }
  function capture() {
    var previous_effect = (
      /** @type {Effect} */
      active_effect
    );
    var previous_reaction = active_reaction;
    var previous_component_context = component_context;
    var previous_batch = (
      /** @type {Batch} */
      current_batch
    );
    return function restore(activate_batch = true) {
      set_active_effect(previous_effect);
      set_active_reaction(previous_reaction);
      set_component_context(previous_component_context);
      if (activate_batch && (previous_effect.f & DESTROYED) === 0) {
        previous_batch?.activate();
        previous_batch?.apply();
      }
    };
  }
  function unset_context(deactivate_batch = true) {
    set_active_effect(null);
    set_active_reaction(null);
    set_component_context(null);
    if (deactivate_batch) current_batch?.deactivate();
  }
  function increment_pending() {
    var effect = (
      /** @type {Effect} */
      active_effect
    );
    var boundary2 = (
      /** @type {Boundary} */
      effect.b
    );
    var batch = (
      /** @type {Batch} */
      current_batch
    );
    var blocking = boundary2.is_rendered();
    boundary2.update_pending_count(1, batch);
    batch.increment(blocking, effect);
    return (skip = false) => {
      boundary2.update_pending_count(-1, batch);
      batch.decrement(blocking, effect, skip);
    };
  }
  // @__NO_SIDE_EFFECTS__
  function derived(fn) {
    var flags2 = DERIVED | DIRTY;
    var parent_derived = active_reaction !== null && (active_reaction.f & DERIVED) !== 0 ? (
      /** @type {Derived} */
      active_reaction
    ) : null;
    if (active_effect !== null) {
      active_effect.f |= EFFECT_PRESERVED;
    }
    const signal = {
      ctx: component_context,
      deps: null,
      effects: null,
      equals,
      f: flags2,
      fn,
      reactions: null,
      rv: 0,
      v: (
        /** @type {V} */
        UNINITIALIZED
      ),
      wv: 0,
      parent: parent_derived ?? active_effect,
      ac: null
    };
    return signal;
  }
  // @__NO_SIDE_EFFECTS__
  function async_derived(fn, label, location) {
    let parent = (
      /** @type {Effect | null} */
      active_effect
    );
    if (parent === null) {
      async_derived_orphan();
    }
    var promise = (
      /** @type {Promise<V>} */
      /** @type {unknown} */
      void 0
    );
    var signal = source(
      /** @type {V} */
      UNINITIALIZED
    );
    var should_suspend = !active_reaction;
    var deferreds = /* @__PURE__ */ new Map();
    async_effect(() => {
      var effect = (
        /** @type {Effect} */
        active_effect
      );
      var d = deferred();
      promise = d.promise;
      try {
        Promise.resolve(fn()).then(d.resolve, d.reject).finally(unset_context);
      } catch (error) {
        d.reject(error);
        unset_context();
      }
      var batch = (
        /** @type {Batch} */
        current_batch
      );
      if (should_suspend) {
        if ((effect.f & REACTION_RAN) !== 0) {
          var decrement_pending = increment_pending();
        }
        if (
          /** @type {Boundary} */
          parent.b.is_rendered()
        ) {
          deferreds.get(batch)?.reject(STALE_REACTION);
          deferreds.delete(batch);
        } else {
          for (const d2 of deferreds.values()) {
            d2.reject(STALE_REACTION);
          }
          deferreds.clear();
        }
        deferreds.set(batch, d);
      }
      const handler = (value, error = void 0) => {
        if (decrement_pending) {
          var skip = error === STALE_REACTION;
          decrement_pending(skip);
        }
        if (error === STALE_REACTION || (effect.f & DESTROYED) !== 0) {
          return;
        }
        batch.activate();
        if (error) {
          signal.f |= ERROR_VALUE;
          internal_set(signal, error);
        } else {
          if ((signal.f & ERROR_VALUE) !== 0) {
            signal.f ^= ERROR_VALUE;
          }
          internal_set(signal, value);
          for (const [b, d2] of deferreds) {
            deferreds.delete(b);
            if (b === batch) break;
            d2.reject(STALE_REACTION);
          }
        }
        batch.deactivate();
      };
      d.promise.then(handler, (e) => handler(null, e || "unknown"));
    });
    teardown(() => {
      for (const d of deferreds.values()) {
        d.reject(STALE_REACTION);
      }
    });
    return new Promise((fulfil) => {
      function next(p) {
        function go() {
          if (p === promise) {
            fulfil(signal);
          } else {
            next(promise);
          }
        }
        p.then(go, go);
      }
      next(promise);
    });
  }
  // @__NO_SIDE_EFFECTS__
  function user_derived(fn) {
    const d = /* @__PURE__ */ derived(fn);
    push_reaction_value(d);
    return d;
  }
  // @__NO_SIDE_EFFECTS__
  function derived_safe_equal(fn) {
    const signal = /* @__PURE__ */ derived(fn);
    signal.equals = safe_equals;
    return signal;
  }
  function destroy_derived_effects(derived2) {
    var effects = derived2.effects;
    if (effects !== null) {
      derived2.effects = null;
      for (var i = 0; i < effects.length; i += 1) {
        destroy_effect(
          /** @type {Effect} */
          effects[i]
        );
      }
    }
  }
  function get_derived_parent_effect(derived2) {
    var parent = derived2.parent;
    while (parent !== null) {
      if ((parent.f & DERIVED) === 0) {
        return (parent.f & DESTROYED) === 0 ? (
          /** @type {Effect} */
          parent
        ) : null;
      }
      parent = parent.parent;
    }
    return null;
  }
  function execute_derived(derived2) {
    var value;
    var prev_active_effect = active_effect;
    set_active_effect(get_derived_parent_effect(derived2));
    {
      try {
        derived2.f &= ~WAS_MARKED;
        destroy_derived_effects(derived2);
        value = update_reaction(derived2);
      } finally {
        set_active_effect(prev_active_effect);
      }
    }
    return value;
  }
  function update_derived(derived2) {
    var old_value = derived2.v;
    var value = execute_derived(derived2);
    if (!derived2.equals(value)) {
      derived2.wv = increment_write_version();
      if (!current_batch?.is_fork || derived2.deps === null) {
        derived2.v = value;
        current_batch?.capture(derived2, old_value, true);
        if (derived2.deps === null) {
          set_signal_status(derived2, CLEAN);
          return;
        }
      }
    }
    if (is_destroying_effect) {
      return;
    }
    if (batch_values !== null) {
      if (effect_tracking() || current_batch?.is_fork) {
        batch_values.set(derived2, value);
      }
    } else {
      update_derived_status(derived2);
    }
  }
  function freeze_derived_effects(derived2) {
    if (derived2.effects === null) return;
    for (const e of derived2.effects) {
      if (e.teardown || e.ac) {
        e.teardown?.();
        e.ac?.abort(STALE_REACTION);
        e.teardown = noop;
        e.ac = null;
        remove_reactions(e, 0);
        destroy_effect_children(e);
      }
    }
  }
  function unfreeze_derived_effects(derived2) {
    if (derived2.effects === null) return;
    for (const e of derived2.effects) {
      if (e.teardown) {
        update_effect(e);
      }
    }
  }
  let eager_effects = /* @__PURE__ */ new Set();
  const old_values = /* @__PURE__ */ new Map();
  let eager_effects_deferred = false;
  function source(v, stack) {
    var signal = {
      f: 0,
      // TODO ideally we could skip this altogether, but it causes type errors
      v,
      reactions: null,
      equals,
      rv: 0,
      wv: 0
    };
    return signal;
  }
  // @__NO_SIDE_EFFECTS__
  function state(v, stack) {
    const s = source(v);
    push_reaction_value(s);
    return s;
  }
  // @__NO_SIDE_EFFECTS__
  function mutable_source(initial_value, immutable = false, trackable = true) {
    const s = source(initial_value);
    if (!immutable) {
      s.equals = safe_equals;
    }
    if (legacy_mode_flag && trackable && component_context !== null && component_context.l !== null) {
      (component_context.l.s ??= []).push(s);
    }
    return s;
  }
  function set(source2, value, should_proxy = false) {
    if (active_reaction !== null && // since we are untracking the function inside `$inspect.with` we need to add this check
    // to ensure we error if state is set inside an inspect effect
    (!untracking || (active_reaction.f & EAGER_EFFECT) !== 0) && is_runes() && (active_reaction.f & (DERIVED | BLOCK_EFFECT | ASYNC | EAGER_EFFECT)) !== 0 && (current_sources === null || !includes.call(current_sources, source2))) {
      state_unsafe_mutation();
    }
    let new_value = should_proxy ? proxy(value) : value;
    return internal_set(source2, new_value, legacy_updates);
  }
  function internal_set(source2, value, updated_during_traversal = null) {
    if (!source2.equals(value)) {
      var old_value = source2.v;
      if (is_destroying_effect) {
        old_values.set(source2, value);
      } else {
        old_values.set(source2, old_value);
      }
      source2.v = value;
      var batch = Batch.ensure();
      batch.capture(source2, old_value);
      if ((source2.f & DERIVED) !== 0) {
        const derived2 = (
          /** @type {Derived} */
          source2
        );
        if ((source2.f & DIRTY) !== 0) {
          execute_derived(derived2);
        }
        if (batch_values === null) {
          update_derived_status(derived2);
        }
      }
      source2.wv = increment_write_version();
      mark_reactions(source2, DIRTY, updated_during_traversal);
      if (is_runes() && active_effect !== null && (active_effect.f & CLEAN) !== 0 && (active_effect.f & (BRANCH_EFFECT | ROOT_EFFECT)) === 0) {
        if (untracked_writes === null) {
          set_untracked_writes([source2]);
        } else {
          untracked_writes.push(source2);
        }
      }
      if (!batch.is_fork && eager_effects.size > 0 && !eager_effects_deferred) {
        flush_eager_effects();
      }
    }
    return value;
  }
  function flush_eager_effects() {
    eager_effects_deferred = false;
    for (const effect of eager_effects) {
      if ((effect.f & CLEAN) !== 0) {
        set_signal_status(effect, MAYBE_DIRTY);
      }
      if (is_dirty(effect)) {
        update_effect(effect);
      }
    }
    eager_effects.clear();
  }
  function increment(source2) {
    set(source2, source2.v + 1);
  }
  function mark_reactions(signal, status, updated_during_traversal) {
    var reactions = signal.reactions;
    if (reactions === null) return;
    var runes = is_runes();
    var length = reactions.length;
    for (var i = 0; i < length; i++) {
      var reaction = reactions[i];
      var flags2 = reaction.f;
      if (!runes && reaction === active_effect) continue;
      var not_dirty = (flags2 & DIRTY) === 0;
      if (not_dirty) {
        set_signal_status(reaction, status);
      }
      if ((flags2 & DERIVED) !== 0) {
        var derived2 = (
          /** @type {Derived} */
          reaction
        );
        batch_values?.delete(derived2);
        if ((flags2 & WAS_MARKED) === 0) {
          if (flags2 & CONNECTED) {
            reaction.f |= WAS_MARKED;
          }
          mark_reactions(derived2, MAYBE_DIRTY, updated_during_traversal);
        }
      } else if (not_dirty) {
        var effect = (
          /** @type {Effect} */
          reaction
        );
        if ((flags2 & BLOCK_EFFECT) !== 0 && eager_block_effects !== null) {
          eager_block_effects.add(effect);
        }
        if (updated_during_traversal !== null) {
          updated_during_traversal.push(effect);
        } else {
          schedule_effect(effect);
        }
      }
    }
  }
  function proxy(value) {
    if (typeof value !== "object" || value === null || STATE_SYMBOL in value) {
      return value;
    }
    const prototype = get_prototype_of(value);
    if (prototype !== object_prototype && prototype !== array_prototype) {
      return value;
    }
    var sources = /* @__PURE__ */ new Map();
    var is_proxied_array = is_array(value);
    var version = /* @__PURE__ */ state(0);
    var parent_version = update_version;
    var with_parent = (fn) => {
      if (update_version === parent_version) {
        return fn();
      }
      var reaction = active_reaction;
      var version2 = update_version;
      set_active_reaction(null);
      set_update_version(parent_version);
      var result = fn();
      set_active_reaction(reaction);
      set_update_version(version2);
      return result;
    };
    if (is_proxied_array) {
      sources.set("length", /* @__PURE__ */ state(
        /** @type {any[]} */
        value.length
      ));
    }
    return new Proxy(
      /** @type {any} */
      value,
      {
        defineProperty(_, prop2, descriptor) {
          if (!("value" in descriptor) || descriptor.configurable === false || descriptor.enumerable === false || descriptor.writable === false) {
            state_descriptors_fixed();
          }
          var s = sources.get(prop2);
          if (s === void 0) {
            with_parent(() => {
              var s2 = /* @__PURE__ */ state(descriptor.value);
              sources.set(prop2, s2);
              return s2;
            });
          } else {
            set(s, descriptor.value, true);
          }
          return true;
        },
        deleteProperty(target, prop2) {
          var s = sources.get(prop2);
          if (s === void 0) {
            if (prop2 in target) {
              const s2 = with_parent(() => /* @__PURE__ */ state(UNINITIALIZED));
              sources.set(prop2, s2);
              increment(version);
            }
          } else {
            set(s, UNINITIALIZED);
            increment(version);
          }
          return true;
        },
        get(target, prop2, receiver) {
          if (prop2 === STATE_SYMBOL) {
            return value;
          }
          var s = sources.get(prop2);
          var exists = prop2 in target;
          if (s === void 0 && (!exists || get_descriptor(target, prop2)?.writable)) {
            s = with_parent(() => {
              var p = proxy(exists ? target[prop2] : UNINITIALIZED);
              var s2 = /* @__PURE__ */ state(p);
              return s2;
            });
            sources.set(prop2, s);
          }
          if (s !== void 0) {
            var v = get(s);
            return v === UNINITIALIZED ? void 0 : v;
          }
          return Reflect.get(target, prop2, receiver);
        },
        getOwnPropertyDescriptor(target, prop2) {
          var descriptor = Reflect.getOwnPropertyDescriptor(target, prop2);
          if (descriptor && "value" in descriptor) {
            var s = sources.get(prop2);
            if (s) descriptor.value = get(s);
          } else if (descriptor === void 0) {
            var source2 = sources.get(prop2);
            var value2 = source2?.v;
            if (source2 !== void 0 && value2 !== UNINITIALIZED) {
              return {
                enumerable: true,
                configurable: true,
                value: value2,
                writable: true
              };
            }
          }
          return descriptor;
        },
        has(target, prop2) {
          if (prop2 === STATE_SYMBOL) {
            return true;
          }
          var s = sources.get(prop2);
          var has = s !== void 0 && s.v !== UNINITIALIZED || Reflect.has(target, prop2);
          if (s !== void 0 || active_effect !== null && (!has || get_descriptor(target, prop2)?.writable)) {
            if (s === void 0) {
              s = with_parent(() => {
                var p = has ? proxy(target[prop2]) : UNINITIALIZED;
                var s2 = /* @__PURE__ */ state(p);
                return s2;
              });
              sources.set(prop2, s);
            }
            var value2 = get(s);
            if (value2 === UNINITIALIZED) {
              return false;
            }
          }
          return has;
        },
        set(target, prop2, value2, receiver) {
          var s = sources.get(prop2);
          var has = prop2 in target;
          if (is_proxied_array && prop2 === "length") {
            for (var i = value2; i < /** @type {Source<number>} */
            s.v; i += 1) {
              var other_s = sources.get(i + "");
              if (other_s !== void 0) {
                set(other_s, UNINITIALIZED);
              } else if (i in target) {
                other_s = with_parent(() => /* @__PURE__ */ state(UNINITIALIZED));
                sources.set(i + "", other_s);
              }
            }
          }
          if (s === void 0) {
            if (!has || get_descriptor(target, prop2)?.writable) {
              s = with_parent(() => /* @__PURE__ */ state(void 0));
              set(s, proxy(value2));
              sources.set(prop2, s);
            }
          } else {
            has = s.v !== UNINITIALIZED;
            var p = with_parent(() => proxy(value2));
            set(s, p);
          }
          var descriptor = Reflect.getOwnPropertyDescriptor(target, prop2);
          if (descriptor?.set) {
            descriptor.set.call(receiver, value2);
          }
          if (!has) {
            if (is_proxied_array && typeof prop2 === "string") {
              var ls = (
                /** @type {Source<number>} */
                sources.get("length")
              );
              var n = Number(prop2);
              if (Number.isInteger(n) && n >= ls.v) {
                set(ls, n + 1);
              }
            }
            increment(version);
          }
          return true;
        },
        ownKeys(target) {
          get(version);
          var own_keys = Reflect.ownKeys(target).filter((key2) => {
            var source3 = sources.get(key2);
            return source3 === void 0 || source3.v !== UNINITIALIZED;
          });
          for (var [key, source2] of sources) {
            if (source2.v !== UNINITIALIZED && !(key in target)) {
              own_keys.push(key);
            }
          }
          return own_keys;
        },
        setPrototypeOf() {
          state_prototype_fixed();
        }
      }
    );
  }
  var $window;
  var is_firefox;
  var first_child_getter;
  var next_sibling_getter;
  function init_operations() {
    if ($window !== void 0) {
      return;
    }
    $window = window;
    is_firefox = /Firefox/.test(navigator.userAgent);
    var element_prototype = Element.prototype;
    var node_prototype = Node.prototype;
    var text_prototype = Text.prototype;
    first_child_getter = get_descriptor(node_prototype, "firstChild").get;
    next_sibling_getter = get_descriptor(node_prototype, "nextSibling").get;
    if (is_extensible(element_prototype)) {
      element_prototype.__click = void 0;
      element_prototype.__className = void 0;
      element_prototype.__attributes = null;
      element_prototype.__style = void 0;
      element_prototype.__e = void 0;
    }
    if (is_extensible(text_prototype)) {
      text_prototype.__t = void 0;
    }
  }
  function create_text(value = "") {
    return document.createTextNode(value);
  }
  // @__NO_SIDE_EFFECTS__
  function get_first_child(node) {
    return (
      /** @type {TemplateNode | null} */
      first_child_getter.call(node)
    );
  }
  // @__NO_SIDE_EFFECTS__
  function get_next_sibling(node) {
    return (
      /** @type {TemplateNode | null} */
      next_sibling_getter.call(node)
    );
  }
  function child(node, is_text) {
    {
      return /* @__PURE__ */ get_first_child(node);
    }
  }
  function first_child(node, is_text = false) {
    {
      var first = /* @__PURE__ */ get_first_child(node);
      if (first instanceof Comment && first.data === "") return /* @__PURE__ */ get_next_sibling(first);
      return first;
    }
  }
  function sibling(node, count = 1, is_text = false) {
    let next_sibling = node;
    while (count--) {
      next_sibling = /** @type {TemplateNode} */
      /* @__PURE__ */ get_next_sibling(next_sibling);
    }
    {
      return next_sibling;
    }
  }
  function clear_text_content(node) {
    node.textContent = "";
  }
  function should_defer_append() {
    return false;
  }
  function create_element(tag, namespace, is) {
    let options = void 0;
    return (
      /** @type {T extends keyof HTMLElementTagNameMap ? HTMLElementTagNameMap[T] : Element} */
      document.createElementNS(NAMESPACE_HTML, tag, options)
    );
  }
  function without_reactive_context(fn) {
    var previous_reaction = active_reaction;
    var previous_effect = active_effect;
    set_active_reaction(null);
    set_active_effect(null);
    try {
      return fn();
    } finally {
      set_active_reaction(previous_reaction);
      set_active_effect(previous_effect);
    }
  }
  function validate_effect(rune) {
    if (active_effect === null) {
      if (active_reaction === null) {
        effect_orphan();
      }
      effect_in_unowned_derived();
    }
    if (is_destroying_effect) {
      effect_in_teardown();
    }
  }
  function push_effect(effect, parent_effect) {
    var parent_last = parent_effect.last;
    if (parent_last === null) {
      parent_effect.last = parent_effect.first = effect;
    } else {
      parent_last.next = effect;
      effect.prev = parent_last;
      parent_effect.last = effect;
    }
  }
  function create_effect(type, fn) {
    var parent = active_effect;
    if (parent !== null && (parent.f & INERT) !== 0) {
      type |= INERT;
    }
    var effect = {
      ctx: component_context,
      deps: null,
      nodes: null,
      f: type | DIRTY | CONNECTED,
      first: null,
      fn,
      last: null,
      next: null,
      parent,
      b: parent && parent.b,
      prev: null,
      teardown: null,
      wv: 0,
      ac: null
    };
    current_batch?.register_created_effect(effect);
    var e = effect;
    if ((type & EFFECT) !== 0) {
      if (collected_effects !== null) {
        collected_effects.push(effect);
      } else {
        Batch.ensure().schedule(effect);
      }
    } else if (fn !== null) {
      try {
        update_effect(effect);
      } catch (e2) {
        destroy_effect(effect);
        throw e2;
      }
      if (e.deps === null && e.teardown === null && e.nodes === null && e.first === e.last && // either `null`, or a singular child
      (e.f & EFFECT_PRESERVED) === 0) {
        e = e.first;
        if ((type & BLOCK_EFFECT) !== 0 && (type & EFFECT_TRANSPARENT) !== 0 && e !== null) {
          e.f |= EFFECT_TRANSPARENT;
        }
      }
    }
    if (e !== null) {
      e.parent = parent;
      if (parent !== null) {
        push_effect(e, parent);
      }
      if (active_reaction !== null && (active_reaction.f & DERIVED) !== 0 && (type & ROOT_EFFECT) === 0) {
        var derived2 = (
          /** @type {Derived} */
          active_reaction
        );
        (derived2.effects ??= []).push(e);
      }
    }
    return effect;
  }
  function effect_tracking() {
    return active_reaction !== null && !untracking;
  }
  function teardown(fn) {
    const effect = create_effect(RENDER_EFFECT, null);
    set_signal_status(effect, CLEAN);
    effect.teardown = fn;
    return effect;
  }
  function user_effect(fn) {
    validate_effect();
    var flags2 = (
      /** @type {Effect} */
      active_effect.f
    );
    var defer = !active_reaction && (flags2 & BRANCH_EFFECT) !== 0 && (flags2 & REACTION_RAN) === 0;
    if (defer) {
      var context = (
        /** @type {ComponentContext} */
        component_context
      );
      (context.e ??= []).push(fn);
    } else {
      return create_user_effect(fn);
    }
  }
  function create_user_effect(fn) {
    return create_effect(EFFECT | USER_EFFECT, fn);
  }
  function user_pre_effect(fn) {
    validate_effect();
    return create_effect(RENDER_EFFECT | USER_EFFECT, fn);
  }
  function component_root(fn) {
    Batch.ensure();
    const effect = create_effect(ROOT_EFFECT | EFFECT_PRESERVED, fn);
    return (options = {}) => {
      return new Promise((fulfil) => {
        if (options.outro) {
          pause_effect(effect, () => {
            destroy_effect(effect);
            fulfil(void 0);
          });
        } else {
          destroy_effect(effect);
          fulfil(void 0);
        }
      });
    };
  }
  function legacy_pre_effect(deps, fn) {
    var context = (
      /** @type {ComponentContextLegacy} */
      component_context
    );
    var token = { effect: null, ran: false, deps };
    context.l.$.push(token);
    token.effect = render_effect(() => {
      deps();
      if (token.ran) return;
      token.ran = true;
      var effect = (
        /** @type {Effect} */
        active_effect
      );
      try {
        set_active_effect(effect.parent);
        untrack(fn);
      } finally {
        set_active_effect(effect);
      }
    });
  }
  function legacy_pre_effect_reset() {
    var context = (
      /** @type {ComponentContextLegacy} */
      component_context
    );
    render_effect(() => {
      for (var token of context.l.$) {
        token.deps();
        var effect = token.effect;
        if ((effect.f & CLEAN) !== 0 && effect.deps !== null) {
          set_signal_status(effect, MAYBE_DIRTY);
        }
        if (is_dirty(effect)) {
          update_effect(effect);
        }
        token.ran = false;
      }
    });
  }
  function async_effect(fn) {
    return create_effect(ASYNC | EFFECT_PRESERVED, fn);
  }
  function render_effect(fn, flags2 = 0) {
    return create_effect(RENDER_EFFECT | flags2, fn);
  }
  function template_effect(fn, sync = [], async = [], blockers = []) {
    flatten(blockers, sync, async, (values) => {
      create_effect(RENDER_EFFECT, () => fn(...values.map(get)));
    });
  }
  function block(fn, flags2 = 0) {
    var effect = create_effect(BLOCK_EFFECT | flags2, fn);
    return effect;
  }
  function branch(fn) {
    return create_effect(BRANCH_EFFECT | EFFECT_PRESERVED, fn);
  }
  function execute_effect_teardown(effect) {
    var teardown2 = effect.teardown;
    if (teardown2 !== null) {
      const previously_destroying_effect = is_destroying_effect;
      const previous_reaction = active_reaction;
      set_is_destroying_effect(true);
      set_active_reaction(null);
      try {
        teardown2.call(null);
      } finally {
        set_is_destroying_effect(previously_destroying_effect);
        set_active_reaction(previous_reaction);
      }
    }
  }
  function destroy_effect_children(signal, remove_dom = false) {
    var effect = signal.first;
    signal.first = signal.last = null;
    while (effect !== null) {
      const controller = effect.ac;
      if (controller !== null) {
        without_reactive_context(() => {
          controller.abort(STALE_REACTION);
        });
      }
      var next = effect.next;
      if ((effect.f & ROOT_EFFECT) !== 0) {
        effect.parent = null;
      } else {
        destroy_effect(effect, remove_dom);
      }
      effect = next;
    }
  }
  function destroy_block_effect_children(signal) {
    var effect = signal.first;
    while (effect !== null) {
      var next = effect.next;
      if ((effect.f & BRANCH_EFFECT) === 0) {
        destroy_effect(effect);
      }
      effect = next;
    }
  }
  function destroy_effect(effect, remove_dom = true) {
    var removed = false;
    if ((remove_dom || (effect.f & HEAD_EFFECT) !== 0) && effect.nodes !== null && effect.nodes.end !== null) {
      remove_effect_dom(
        effect.nodes.start,
        /** @type {TemplateNode} */
        effect.nodes.end
      );
      removed = true;
    }
    set_signal_status(effect, DESTROYING);
    destroy_effect_children(effect, remove_dom && !removed);
    remove_reactions(effect, 0);
    var transitions = effect.nodes && effect.nodes.t;
    if (transitions !== null) {
      for (const transition of transitions) {
        transition.stop();
      }
    }
    execute_effect_teardown(effect);
    effect.f ^= DESTROYING;
    effect.f |= DESTROYED;
    var parent = effect.parent;
    if (parent !== null && parent.first !== null) {
      unlink_effect(effect);
    }
    effect.next = effect.prev = effect.teardown = effect.ctx = effect.deps = effect.fn = effect.nodes = effect.ac = effect.b = null;
  }
  function remove_effect_dom(node, end) {
    while (node !== null) {
      var next = node === end ? null : /* @__PURE__ */ get_next_sibling(node);
      node.remove();
      node = next;
    }
  }
  function unlink_effect(effect) {
    var parent = effect.parent;
    var prev = effect.prev;
    var next = effect.next;
    if (prev !== null) prev.next = next;
    if (next !== null) next.prev = prev;
    if (parent !== null) {
      if (parent.first === effect) parent.first = next;
      if (parent.last === effect) parent.last = prev;
    }
  }
  function pause_effect(effect, callback, destroy = true) {
    var transitions = [];
    pause_children(effect, transitions, true);
    var fn = () => {
      if (destroy) destroy_effect(effect);
      if (callback) callback();
    };
    var remaining = transitions.length;
    if (remaining > 0) {
      var check = () => --remaining || fn();
      for (var transition of transitions) {
        transition.out(check);
      }
    } else {
      fn();
    }
  }
  function pause_children(effect, transitions, local) {
    if ((effect.f & INERT) !== 0) return;
    effect.f ^= INERT;
    var t = effect.nodes && effect.nodes.t;
    if (t !== null) {
      for (const transition of t) {
        if (transition.is_global || local) {
          transitions.push(transition);
        }
      }
    }
    var child2 = effect.first;
    while (child2 !== null) {
      var sibling2 = child2.next;
      var transparent = (child2.f & EFFECT_TRANSPARENT) !== 0 || // If this is a branch effect without a block effect parent,
      // it means the parent block effect was pruned. In that case,
      // transparency information was transferred to the branch effect.
      (child2.f & BRANCH_EFFECT) !== 0 && (effect.f & BLOCK_EFFECT) !== 0;
      pause_children(child2, transitions, transparent ? local : false);
      child2 = sibling2;
    }
  }
  function resume_effect(effect) {
    resume_children(effect, true);
  }
  function resume_children(effect, local) {
    if ((effect.f & INERT) === 0) return;
    effect.f ^= INERT;
    if ((effect.f & CLEAN) === 0) {
      set_signal_status(effect, DIRTY);
      Batch.ensure().schedule(effect);
    }
    var child2 = effect.first;
    while (child2 !== null) {
      var sibling2 = child2.next;
      var transparent = (child2.f & EFFECT_TRANSPARENT) !== 0 || (child2.f & BRANCH_EFFECT) !== 0;
      resume_children(child2, transparent ? local : false);
      child2 = sibling2;
    }
    var t = effect.nodes && effect.nodes.t;
    if (t !== null) {
      for (const transition of t) {
        if (transition.is_global || local) {
          transition.in();
        }
      }
    }
  }
  function move_effect(effect, fragment) {
    if (!effect.nodes) return;
    var node = effect.nodes.start;
    var end = effect.nodes.end;
    while (node !== null) {
      var next = node === end ? null : /* @__PURE__ */ get_next_sibling(node);
      fragment.append(node);
      node = next;
    }
  }
  let is_updating_effect = false;
  let is_destroying_effect = false;
  function set_is_destroying_effect(value) {
    is_destroying_effect = value;
  }
  let active_reaction = null;
  let untracking = false;
  function set_active_reaction(reaction) {
    active_reaction = reaction;
  }
  let active_effect = null;
  function set_active_effect(effect) {
    active_effect = effect;
  }
  let current_sources = null;
  function push_reaction_value(value) {
    if (active_reaction !== null && true) {
      if (current_sources === null) {
        current_sources = [value];
      } else {
        current_sources.push(value);
      }
    }
  }
  let new_deps = null;
  let skipped_deps = 0;
  let untracked_writes = null;
  function set_untracked_writes(value) {
    untracked_writes = value;
  }
  let write_version = 1;
  let read_version = 0;
  let update_version = read_version;
  function set_update_version(value) {
    update_version = value;
  }
  function increment_write_version() {
    return ++write_version;
  }
  function is_dirty(reaction) {
    var flags2 = reaction.f;
    if ((flags2 & DIRTY) !== 0) {
      return true;
    }
    if (flags2 & DERIVED) {
      reaction.f &= ~WAS_MARKED;
    }
    if ((flags2 & MAYBE_DIRTY) !== 0) {
      var dependencies = (
        /** @type {Value[]} */
        reaction.deps
      );
      var length = dependencies.length;
      for (var i = 0; i < length; i++) {
        var dependency = dependencies[i];
        if (is_dirty(
          /** @type {Derived} */
          dependency
        )) {
          update_derived(
            /** @type {Derived} */
            dependency
          );
        }
        if (dependency.wv > reaction.wv) {
          return true;
        }
      }
      if ((flags2 & CONNECTED) !== 0 && // During time traveling we don't want to reset the status so that
      // traversal of the graph in the other batches still happens
      batch_values === null) {
        set_signal_status(reaction, CLEAN);
      }
    }
    return false;
  }
  function schedule_possible_effect_self_invalidation(signal, effect, root2 = true) {
    var reactions = signal.reactions;
    if (reactions === null) return;
    if (current_sources !== null && includes.call(current_sources, signal)) {
      return;
    }
    for (var i = 0; i < reactions.length; i++) {
      var reaction = reactions[i];
      if ((reaction.f & DERIVED) !== 0) {
        schedule_possible_effect_self_invalidation(
          /** @type {Derived} */
          reaction,
          effect,
          false
        );
      } else if (effect === reaction) {
        if (root2) {
          set_signal_status(reaction, DIRTY);
        } else if ((reaction.f & CLEAN) !== 0) {
          set_signal_status(reaction, MAYBE_DIRTY);
        }
        schedule_effect(
          /** @type {Effect} */
          reaction
        );
      }
    }
  }
  function update_reaction(reaction) {
    var previous_deps = new_deps;
    var previous_skipped_deps = skipped_deps;
    var previous_untracked_writes = untracked_writes;
    var previous_reaction = active_reaction;
    var previous_sources = current_sources;
    var previous_component_context = component_context;
    var previous_untracking = untracking;
    var previous_update_version = update_version;
    var flags2 = reaction.f;
    new_deps = /** @type {null | Value[]} */
    null;
    skipped_deps = 0;
    untracked_writes = null;
    active_reaction = (flags2 & (BRANCH_EFFECT | ROOT_EFFECT)) === 0 ? reaction : null;
    current_sources = null;
    set_component_context(reaction.ctx);
    untracking = false;
    update_version = ++read_version;
    if (reaction.ac !== null) {
      without_reactive_context(() => {
        reaction.ac.abort(STALE_REACTION);
      });
      reaction.ac = null;
    }
    try {
      reaction.f |= REACTION_IS_UPDATING;
      var fn = (
        /** @type {Function} */
        reaction.fn
      );
      var result = fn();
      reaction.f |= REACTION_RAN;
      var deps = reaction.deps;
      var is_fork = current_batch?.is_fork;
      if (new_deps !== null) {
        var i;
        if (!is_fork) {
          remove_reactions(reaction, skipped_deps);
        }
        if (deps !== null && skipped_deps > 0) {
          deps.length = skipped_deps + new_deps.length;
          for (i = 0; i < new_deps.length; i++) {
            deps[skipped_deps + i] = new_deps[i];
          }
        } else {
          reaction.deps = deps = new_deps;
        }
        if (effect_tracking() && (reaction.f & CONNECTED) !== 0) {
          for (i = skipped_deps; i < deps.length; i++) {
            (deps[i].reactions ??= []).push(reaction);
          }
        }
      } else if (!is_fork && deps !== null && skipped_deps < deps.length) {
        remove_reactions(reaction, skipped_deps);
        deps.length = skipped_deps;
      }
      if (is_runes() && untracked_writes !== null && !untracking && deps !== null && (reaction.f & (DERIVED | MAYBE_DIRTY | DIRTY)) === 0) {
        for (i = 0; i < /** @type {Source[]} */
        untracked_writes.length; i++) {
          schedule_possible_effect_self_invalidation(
            untracked_writes[i],
            /** @type {Effect} */
            reaction
          );
        }
      }
      if (previous_reaction !== null && previous_reaction !== reaction) {
        read_version++;
        if (previous_reaction.deps !== null) {
          for (let i2 = 0; i2 < previous_skipped_deps; i2 += 1) {
            previous_reaction.deps[i2].rv = read_version;
          }
        }
        if (previous_deps !== null) {
          for (const dep of previous_deps) {
            dep.rv = read_version;
          }
        }
        if (untracked_writes !== null) {
          if (previous_untracked_writes === null) {
            previous_untracked_writes = untracked_writes;
          } else {
            previous_untracked_writes.push(.../** @type {Source[]} */
            untracked_writes);
          }
        }
      }
      if ((reaction.f & ERROR_VALUE) !== 0) {
        reaction.f ^= ERROR_VALUE;
      }
      return result;
    } catch (error) {
      return handle_error(error);
    } finally {
      reaction.f ^= REACTION_IS_UPDATING;
      new_deps = previous_deps;
      skipped_deps = previous_skipped_deps;
      untracked_writes = previous_untracked_writes;
      active_reaction = previous_reaction;
      current_sources = previous_sources;
      set_component_context(previous_component_context);
      untracking = previous_untracking;
      update_version = previous_update_version;
    }
  }
  function remove_reaction(signal, dependency) {
    let reactions = dependency.reactions;
    if (reactions !== null) {
      var index2 = index_of.call(reactions, signal);
      if (index2 !== -1) {
        var new_length = reactions.length - 1;
        if (new_length === 0) {
          reactions = dependency.reactions = null;
        } else {
          reactions[index2] = reactions[new_length];
          reactions.pop();
        }
      }
    }
    if (reactions === null && (dependency.f & DERIVED) !== 0 && // Destroying a child effect while updating a parent effect can cause a dependency to appear
    // to be unused, when in fact it is used by the currently-updating parent. Checking `new_deps`
    // allows us to skip the expensive work of disconnecting and immediately reconnecting it
    (new_deps === null || !includes.call(new_deps, dependency))) {
      var derived2 = (
        /** @type {Derived} */
        dependency
      );
      if ((derived2.f & CONNECTED) !== 0) {
        derived2.f ^= CONNECTED;
        derived2.f &= ~WAS_MARKED;
      }
      update_derived_status(derived2);
      freeze_derived_effects(derived2);
      remove_reactions(derived2, 0);
    }
  }
  function remove_reactions(signal, start_index) {
    var dependencies = signal.deps;
    if (dependencies === null) return;
    for (var i = start_index; i < dependencies.length; i++) {
      remove_reaction(signal, dependencies[i]);
    }
  }
  function update_effect(effect) {
    var flags2 = effect.f;
    if ((flags2 & DESTROYED) !== 0) {
      return;
    }
    set_signal_status(effect, CLEAN);
    var previous_effect = active_effect;
    var was_updating_effect = is_updating_effect;
    active_effect = effect;
    is_updating_effect = true;
    try {
      if ((flags2 & (BLOCK_EFFECT | MANAGED_EFFECT)) !== 0) {
        destroy_block_effect_children(effect);
      } else {
        destroy_effect_children(effect);
      }
      execute_effect_teardown(effect);
      var teardown2 = update_reaction(effect);
      effect.teardown = typeof teardown2 === "function" ? teardown2 : null;
      effect.wv = write_version;
      var dep;
      if (DEV && tracing_mode_flag && (effect.f & DIRTY) !== 0 && effect.deps !== null) ;
    } finally {
      is_updating_effect = was_updating_effect;
      active_effect = previous_effect;
    }
  }
  function get(signal) {
    var flags2 = signal.f;
    var is_derived = (flags2 & DERIVED) !== 0;
    if (active_reaction !== null && !untracking) {
      var destroyed = active_effect !== null && (active_effect.f & DESTROYED) !== 0;
      if (!destroyed && (current_sources === null || !includes.call(current_sources, signal))) {
        var deps = active_reaction.deps;
        if ((active_reaction.f & REACTION_IS_UPDATING) !== 0) {
          if (signal.rv < read_version) {
            signal.rv = read_version;
            if (new_deps === null && deps !== null && deps[skipped_deps] === signal) {
              skipped_deps++;
            } else if (new_deps === null) {
              new_deps = [signal];
            } else {
              new_deps.push(signal);
            }
          }
        } else {
          (active_reaction.deps ??= []).push(signal);
          var reactions = signal.reactions;
          if (reactions === null) {
            signal.reactions = [active_reaction];
          } else if (!includes.call(reactions, active_reaction)) {
            reactions.push(active_reaction);
          }
        }
      }
    }
    if (is_destroying_effect && old_values.has(signal)) {
      return old_values.get(signal);
    }
    if (is_derived) {
      var derived2 = (
        /** @type {Derived} */
        signal
      );
      if (is_destroying_effect) {
        var value = derived2.v;
        if ((derived2.f & CLEAN) === 0 && derived2.reactions !== null || depends_on_old_values(derived2)) {
          value = execute_derived(derived2);
        }
        old_values.set(derived2, value);
        return value;
      }
      var should_connect = (derived2.f & CONNECTED) === 0 && !untracking && active_reaction !== null && (is_updating_effect || (active_reaction.f & CONNECTED) !== 0);
      var is_new = (derived2.f & REACTION_RAN) === 0;
      if (is_dirty(derived2)) {
        if (should_connect) {
          derived2.f |= CONNECTED;
        }
        update_derived(derived2);
      }
      if (should_connect && !is_new) {
        unfreeze_derived_effects(derived2);
        reconnect(derived2);
      }
    }
    if (batch_values?.has(signal)) {
      return batch_values.get(signal);
    }
    if ((signal.f & ERROR_VALUE) !== 0) {
      throw signal.v;
    }
    return signal.v;
  }
  function reconnect(derived2) {
    derived2.f |= CONNECTED;
    if (derived2.deps === null) return;
    for (const dep of derived2.deps) {
      (dep.reactions ??= []).push(derived2);
      if ((dep.f & DERIVED) !== 0 && (dep.f & CONNECTED) === 0) {
        unfreeze_derived_effects(
          /** @type {Derived} */
          dep
        );
        reconnect(
          /** @type {Derived} */
          dep
        );
      }
    }
  }
  function depends_on_old_values(derived2) {
    if (derived2.v === UNINITIALIZED) return true;
    if (derived2.deps === null) return false;
    for (const dep of derived2.deps) {
      if (old_values.has(dep)) {
        return true;
      }
      if ((dep.f & DERIVED) !== 0 && depends_on_old_values(
        /** @type {Derived} */
        dep
      )) {
        return true;
      }
    }
    return false;
  }
  function untrack(fn) {
    var previous_untracking = untracking;
    try {
      untracking = true;
      return fn();
    } finally {
      untracking = previous_untracking;
    }
  }
  function deep_read_state(value) {
    if (typeof value !== "object" || !value || value instanceof EventTarget) {
      return;
    }
    if (STATE_SYMBOL in value) {
      deep_read(value);
    } else if (!Array.isArray(value)) {
      for (let key in value) {
        const prop2 = value[key];
        if (typeof prop2 === "object" && prop2 && STATE_SYMBOL in prop2) {
          deep_read(prop2);
        }
      }
    }
  }
  function deep_read(value, visited = /* @__PURE__ */ new Set()) {
    if (typeof value === "object" && value !== null && // We don't want to traverse DOM elements
    !(value instanceof EventTarget) && !visited.has(value)) {
      visited.add(value);
      if (value instanceof Date) {
        value.getTime();
      }
      for (let key in value) {
        try {
          deep_read(value[key], visited);
        } catch (e) {
        }
      }
      const proto = get_prototype_of(value);
      if (proto !== Object.prototype && proto !== Array.prototype && proto !== Map.prototype && proto !== Set.prototype && proto !== Date.prototype) {
        const descriptors = get_descriptors(proto);
        for (let key in descriptors) {
          const get2 = descriptors[key].get;
          if (get2) {
            try {
              get2.call(value);
            } catch (e) {
            }
          }
        }
      }
    }
  }
  const PASSIVE_EVENTS = ["touchstart", "touchmove"];
  function is_passive_event(name) {
    return PASSIVE_EVENTS.includes(name);
  }
  const event_symbol = /* @__PURE__ */ Symbol("events");
  const all_registered_events = /* @__PURE__ */ new Set();
  const root_event_handles = /* @__PURE__ */ new Set();
  function create_event(event_name, dom, handler, options = {}) {
    function target_handler(event2) {
      if (!options.capture) {
        handle_event_propagation.call(dom, event2);
      }
      if (!event2.cancelBubble) {
        return without_reactive_context(() => {
          return handler?.call(this, event2);
        });
      }
    }
    if (event_name.startsWith("pointer") || event_name.startsWith("touch") || event_name === "wheel") {
      queue_micro_task(() => {
        dom.addEventListener(event_name, target_handler, options);
      });
    } else {
      dom.addEventListener(event_name, target_handler, options);
    }
    return target_handler;
  }
  function event(event_name, dom, handler, capture2, passive) {
    var options = { capture: capture2, passive };
    var target_handler = create_event(event_name, dom, handler, options);
    if (dom === document.body || // @ts-ignore
    dom === window || // @ts-ignore
    dom === document || // Firefox has quirky behavior, it can happen that we still get "canplay" events when the element is already removed
    dom instanceof HTMLMediaElement) {
      teardown(() => {
        dom.removeEventListener(event_name, target_handler, options);
      });
    }
  }
  let last_propagated_event = null;
  function handle_event_propagation(event2) {
    var handler_element = this;
    var owner_document = (
      /** @type {Node} */
      handler_element.ownerDocument
    );
    var event_name = event2.type;
    var path = event2.composedPath?.() || [];
    var current_target = (
      /** @type {null | Element} */
      path[0] || event2.target
    );
    last_propagated_event = event2;
    var path_idx = 0;
    var handled_at = last_propagated_event === event2 && event2[event_symbol];
    if (handled_at) {
      var at_idx = path.indexOf(handled_at);
      if (at_idx !== -1 && (handler_element === document || handler_element === /** @type {any} */
      window)) {
        event2[event_symbol] = handler_element;
        return;
      }
      var handler_idx = path.indexOf(handler_element);
      if (handler_idx === -1) {
        return;
      }
      if (at_idx <= handler_idx) {
        path_idx = at_idx;
      }
    }
    current_target = /** @type {Element} */
    path[path_idx] || event2.target;
    if (current_target === handler_element) return;
    define_property(event2, "currentTarget", {
      configurable: true,
      get() {
        return current_target || owner_document;
      }
    });
    var previous_reaction = active_reaction;
    var previous_effect = active_effect;
    set_active_reaction(null);
    set_active_effect(null);
    try {
      var throw_error;
      var other_errors = [];
      while (current_target !== null) {
        var parent_element = current_target.assignedSlot || current_target.parentNode || /** @type {any} */
        current_target.host || null;
        try {
          var delegated = current_target[event_symbol]?.[event_name];
          if (delegated != null && (!/** @type {any} */
          current_target.disabled || // DOM could've been updated already by the time this is reached, so we check this as well
          // -> the target could not have been disabled because it emits the event in the first place
          event2.target === current_target)) {
            delegated.call(current_target, event2);
          }
        } catch (error) {
          if (throw_error) {
            other_errors.push(error);
          } else {
            throw_error = error;
          }
        }
        if (event2.cancelBubble || parent_element === handler_element || parent_element === null) {
          break;
        }
        current_target = parent_element;
      }
      if (throw_error) {
        for (let error of other_errors) {
          queueMicrotask(() => {
            throw error;
          });
        }
        throw throw_error;
      }
    } finally {
      event2[event_symbol] = handler_element;
      delete event2.currentTarget;
      set_active_reaction(previous_reaction);
      set_active_effect(previous_effect);
    }
  }
  const policy = (
    // We gotta write it like this because after downleveling the pure comment may end up in the wrong location
    globalThis?.window?.trustedTypes && /* @__PURE__ */ globalThis.window.trustedTypes.createPolicy("svelte-trusted-html", {
      /** @param {string} html */
      createHTML: (html) => {
        return html;
      }
    })
  );
  function create_trusted_html(html) {
    return (
      /** @type {string} */
      policy?.createHTML(html) ?? html
    );
  }
  function create_fragment_from_html(html) {
    var elem = create_element("template");
    elem.innerHTML = create_trusted_html(html.replaceAll("<!>", "<!---->"));
    return elem.content;
  }
  function assign_nodes(start, end) {
    var effect = (
      /** @type {Effect} */
      active_effect
    );
    if (effect.nodes === null) {
      effect.nodes = { start, end, a: null, t: null };
    }
  }
  // @__NO_SIDE_EFFECTS__
  function from_html(content, flags2) {
    var is_fragment = (flags2 & TEMPLATE_FRAGMENT) !== 0;
    var use_import_node = (flags2 & TEMPLATE_USE_IMPORT_NODE) !== 0;
    var node;
    var has_start = !content.startsWith("<!>");
    return () => {
      if (node === void 0) {
        node = create_fragment_from_html(has_start ? content : "<!>" + content);
        if (!is_fragment) node = /** @type {TemplateNode} */
        /* @__PURE__ */ get_first_child(node);
      }
      var clone = (
        /** @type {TemplateNode} */
        use_import_node || is_firefox ? document.importNode(node, true) : node.cloneNode(true)
      );
      if (is_fragment) {
        var start = (
          /** @type {TemplateNode} */
          /* @__PURE__ */ get_first_child(clone)
        );
        var end = (
          /** @type {TemplateNode} */
          clone.lastChild
        );
        assign_nodes(start, end);
      } else {
        assign_nodes(clone, clone);
      }
      return clone;
    };
  }
  function text(value = "") {
    {
      var t = create_text(value + "");
      assign_nodes(t, t);
      return t;
    }
  }
  function append(anchor, dom) {
    if (anchor === null) {
      return;
    }
    anchor.before(
      /** @type {Node} */
      dom
    );
  }
  function set_text(text2, value) {
    var str = value == null ? "" : typeof value === "object" ? `${value}` : value;
    if (str !== (text2.__t ??= text2.nodeValue)) {
      text2.__t = str;
      text2.nodeValue = `${str}`;
    }
  }
  function mount(component, options) {
    return _mount(component, options);
  }
  const listeners = /* @__PURE__ */ new Map();
  function _mount(Component, { target, anchor, props = {}, events, context, intro = true, transformError }) {
    init_operations();
    var component = void 0;
    var unmount2 = component_root(() => {
      var anchor_node = anchor ?? target.appendChild(create_text());
      boundary(
        /** @type {TemplateNode} */
        anchor_node,
        {
          pending: () => {
          }
        },
        (anchor_node2) => {
          push({});
          var ctx = (
            /** @type {ComponentContext} */
            component_context
          );
          if (context) ctx.c = context;
          if (events) {
            props.$$events = events;
          }
          component = Component(anchor_node2, props) || {};
          pop();
        },
        transformError
      );
      var registered_events = /* @__PURE__ */ new Set();
      var event_handle = (events2) => {
        for (var i = 0; i < events2.length; i++) {
          var event_name = events2[i];
          if (registered_events.has(event_name)) continue;
          registered_events.add(event_name);
          var passive = is_passive_event(event_name);
          for (const node of [target, document]) {
            var counts = listeners.get(node);
            if (counts === void 0) {
              counts = /* @__PURE__ */ new Map();
              listeners.set(node, counts);
            }
            var count = counts.get(event_name);
            if (count === void 0) {
              node.addEventListener(event_name, handle_event_propagation, { passive });
              counts.set(event_name, 1);
            } else {
              counts.set(event_name, count + 1);
            }
          }
        }
      };
      event_handle(array_from(all_registered_events));
      root_event_handles.add(event_handle);
      return () => {
        for (var event_name of registered_events) {
          for (const node of [target, document]) {
            var counts = (
              /** @type {Map<string, number>} */
              listeners.get(node)
            );
            var count = (
              /** @type {number} */
              counts.get(event_name)
            );
            if (--count == 0) {
              node.removeEventListener(event_name, handle_event_propagation);
              counts.delete(event_name);
              if (counts.size === 0) {
                listeners.delete(node);
              }
            } else {
              counts.set(event_name, count);
            }
          }
        }
        root_event_handles.delete(event_handle);
        if (anchor_node !== anchor) {
          anchor_node.parentNode?.removeChild(anchor_node);
        }
      };
    });
    mounted_components.set(component, unmount2);
    return component;
  }
  let mounted_components = /* @__PURE__ */ new WeakMap();
  function unmount(component, options) {
    const fn = mounted_components.get(component);
    if (fn) {
      mounted_components.delete(component);
      return fn(options);
    }
    return Promise.resolve();
  }
  class BranchManager {
    /** @type {TemplateNode} */
    anchor;
    /** @type {Map<Batch, Key>} */
    #batches = /* @__PURE__ */ new Map();
    /**
     * Map of keys to effects that are currently rendered in the DOM.
     * These effects are visible and actively part of the document tree.
     * Example:
     * ```
     * {#if condition}
     * 	foo
     * {:else}
     * 	bar
     * {/if}
     * ```
     * Can result in the entries `true->Effect` and `false->Effect`
     * @type {Map<Key, Effect>}
     */
    #onscreen = /* @__PURE__ */ new Map();
    /**
     * Similar to #onscreen with respect to the keys, but contains branches that are not yet
     * in the DOM, because their insertion is deferred.
     * @type {Map<Key, Branch>}
     */
    #offscreen = /* @__PURE__ */ new Map();
    /**
     * Keys of effects that are currently outroing
     * @type {Set<Key>}
     */
    #outroing = /* @__PURE__ */ new Set();
    /**
     * Whether to pause (i.e. outro) on change, or destroy immediately.
     * This is necessary for `<svelte:element>`
     */
    #transition = true;
    /**
     * @param {TemplateNode} anchor
     * @param {boolean} transition
     */
    constructor(anchor, transition = true) {
      this.anchor = anchor;
      this.#transition = transition;
    }
    /**
     * @param {Batch} batch
     */
    #commit = (batch) => {
      if (!this.#batches.has(batch)) return;
      var key = (
        /** @type {Key} */
        this.#batches.get(batch)
      );
      var onscreen = this.#onscreen.get(key);
      if (onscreen) {
        resume_effect(onscreen);
        this.#outroing.delete(key);
      } else {
        var offscreen = this.#offscreen.get(key);
        if (offscreen) {
          this.#onscreen.set(key, offscreen.effect);
          this.#offscreen.delete(key);
          offscreen.fragment.lastChild.remove();
          this.anchor.before(offscreen.fragment);
          onscreen = offscreen.effect;
        }
      }
      for (const [b, k] of this.#batches) {
        this.#batches.delete(b);
        if (b === batch) {
          break;
        }
        const offscreen2 = this.#offscreen.get(k);
        if (offscreen2) {
          destroy_effect(offscreen2.effect);
          this.#offscreen.delete(k);
        }
      }
      for (const [k, effect] of this.#onscreen) {
        if (k === key || this.#outroing.has(k)) continue;
        const on_destroy = () => {
          const keys = Array.from(this.#batches.values());
          if (keys.includes(k)) {
            var fragment = document.createDocumentFragment();
            move_effect(effect, fragment);
            fragment.append(create_text());
            this.#offscreen.set(k, { effect, fragment });
          } else {
            destroy_effect(effect);
          }
          this.#outroing.delete(k);
          this.#onscreen.delete(k);
        };
        if (this.#transition || !onscreen) {
          this.#outroing.add(k);
          pause_effect(effect, on_destroy, false);
        } else {
          on_destroy();
        }
      }
    };
    /**
     * @param {Batch} batch
     */
    #discard = (batch) => {
      this.#batches.delete(batch);
      const keys = Array.from(this.#batches.values());
      for (const [k, branch2] of this.#offscreen) {
        if (!keys.includes(k)) {
          destroy_effect(branch2.effect);
          this.#offscreen.delete(k);
        }
      }
    };
    /**
     *
     * @param {any} key
     * @param {null | ((target: TemplateNode) => void)} fn
     */
    ensure(key, fn) {
      var batch = (
        /** @type {Batch} */
        current_batch
      );
      var defer = should_defer_append();
      if (fn && !this.#onscreen.has(key) && !this.#offscreen.has(key)) {
        if (defer) {
          var fragment = document.createDocumentFragment();
          var target = create_text();
          fragment.append(target);
          this.#offscreen.set(key, {
            effect: branch(() => fn(target)),
            fragment
          });
        } else {
          this.#onscreen.set(
            key,
            branch(() => fn(this.anchor))
          );
        }
      }
      this.#batches.set(batch, key);
      if (defer) {
        for (const [k, effect] of this.#onscreen) {
          if (k === key) {
            batch.unskip_effect(effect);
          } else {
            batch.skip_effect(effect);
          }
        }
        for (const [k, branch2] of this.#offscreen) {
          if (k === key) {
            batch.unskip_effect(branch2.effect);
          } else {
            batch.skip_effect(branch2.effect);
          }
        }
        batch.oncommit(this.#commit);
        batch.ondiscard(this.#discard);
      } else {
        this.#commit(batch);
      }
    }
  }
  function if_block(node, fn, elseif = false) {
    var branches = new BranchManager(node);
    var flags2 = elseif ? EFFECT_TRANSPARENT : 0;
    function update_branch(key, fn2) {
      branches.ensure(key, fn2);
    }
    block(() => {
      var has_branch = false;
      fn((fn2, key = 0) => {
        has_branch = true;
        update_branch(key, fn2);
      });
      if (!has_branch) {
        update_branch(-1, null);
      }
    }, flags2);
  }
  function index(_, i) {
    return i;
  }
  function pause_effects(state2, to_destroy, controlled_anchor) {
    var transitions = [];
    var length = to_destroy.length;
    var group;
    var remaining = to_destroy.length;
    for (var i = 0; i < length; i++) {
      let effect = to_destroy[i];
      pause_effect(
        effect,
        () => {
          if (group) {
            group.pending.delete(effect);
            group.done.add(effect);
            if (group.pending.size === 0) {
              var groups = (
                /** @type {Set<EachOutroGroup>} */
                state2.outrogroups
              );
              destroy_effects(state2, array_from(group.done));
              groups.delete(group);
              if (groups.size === 0) {
                state2.outrogroups = null;
              }
            }
          } else {
            remaining -= 1;
          }
        },
        false
      );
    }
    if (remaining === 0) {
      var fast_path = transitions.length === 0 && controlled_anchor !== null;
      if (fast_path) {
        var anchor = (
          /** @type {Element} */
          controlled_anchor
        );
        var parent_node = (
          /** @type {Element} */
          anchor.parentNode
        );
        clear_text_content(parent_node);
        parent_node.append(anchor);
        state2.items.clear();
      }
      destroy_effects(state2, to_destroy, !fast_path);
    } else {
      group = {
        pending: new Set(to_destroy),
        done: /* @__PURE__ */ new Set()
      };
      (state2.outrogroups ??= /* @__PURE__ */ new Set()).add(group);
    }
  }
  function destroy_effects(state2, to_destroy, remove_dom = true) {
    var preserved_effects;
    if (state2.pending.size > 0) {
      preserved_effects = /* @__PURE__ */ new Set();
      for (const keys of state2.pending.values()) {
        for (const key of keys) {
          preserved_effects.add(
            /** @type {EachItem} */
            state2.items.get(key).e
          );
        }
      }
    }
    for (var i = 0; i < to_destroy.length; i++) {
      var e = to_destroy[i];
      if (preserved_effects?.has(e)) {
        e.f |= EFFECT_OFFSCREEN;
        const fragment = document.createDocumentFragment();
        move_effect(e, fragment);
      } else {
        destroy_effect(to_destroy[i], remove_dom);
      }
    }
  }
  var offscreen_anchor;
  function each(node, flags2, get_collection, get_key, render_fn, fallback_fn = null) {
    var anchor = node;
    var items = /* @__PURE__ */ new Map();
    {
      var parent_node = (
        /** @type {Element} */
        node
      );
      anchor = parent_node.appendChild(create_text());
    }
    var fallback = null;
    var each_array = /* @__PURE__ */ derived_safe_equal(() => {
      var collection = get_collection();
      return is_array(collection) ? collection : collection == null ? [] : array_from(collection);
    });
    var array;
    var pending = /* @__PURE__ */ new Map();
    var first_run = true;
    function commit(batch) {
      if ((state2.effect.f & DESTROYED) !== 0) {
        return;
      }
      state2.pending.delete(batch);
      state2.fallback = fallback;
      reconcile(state2, array, anchor, flags2, get_key);
      if (fallback !== null) {
        if (array.length === 0) {
          if ((fallback.f & EFFECT_OFFSCREEN) === 0) {
            resume_effect(fallback);
          } else {
            fallback.f ^= EFFECT_OFFSCREEN;
            move(fallback, null, anchor);
          }
        } else {
          pause_effect(fallback, () => {
            fallback = null;
          });
        }
      }
    }
    function discard(batch) {
      state2.pending.delete(batch);
    }
    var effect = block(() => {
      array = /** @type {V[]} */
      get(each_array);
      var length = array.length;
      var keys = /* @__PURE__ */ new Set();
      var batch = (
        /** @type {Batch} */
        current_batch
      );
      var defer = should_defer_append();
      for (var index2 = 0; index2 < length; index2 += 1) {
        var value = array[index2];
        var key = get_key(value, index2);
        var item = first_run ? null : items.get(key);
        if (item) {
          if (item.v) internal_set(item.v, value);
          if (item.i) internal_set(item.i, index2);
          if (defer) {
            batch.unskip_effect(item.e);
          }
        } else {
          item = create_item(
            items,
            first_run ? anchor : offscreen_anchor ??= create_text(),
            value,
            key,
            index2,
            render_fn,
            flags2,
            get_collection
          );
          if (!first_run) {
            item.e.f |= EFFECT_OFFSCREEN;
          }
          items.set(key, item);
        }
        keys.add(key);
      }
      if (length === 0 && fallback_fn && !fallback) {
        if (first_run) {
          fallback = branch(() => fallback_fn(anchor));
        } else {
          fallback = branch(() => fallback_fn(offscreen_anchor ??= create_text()));
          fallback.f |= EFFECT_OFFSCREEN;
        }
      }
      if (length > keys.size) {
        {
          each_key_duplicate();
        }
      }
      if (!first_run) {
        pending.set(batch, keys);
        if (defer) {
          for (const [key2, item2] of items) {
            if (!keys.has(key2)) {
              batch.skip_effect(item2.e);
            }
          }
          batch.oncommit(commit);
          batch.ondiscard(discard);
        } else {
          commit(batch);
        }
      }
      get(each_array);
    });
    var state2 = { effect, items, pending, outrogroups: null, fallback };
    first_run = false;
  }
  function skip_to_branch(effect) {
    while (effect !== null && (effect.f & BRANCH_EFFECT) === 0) {
      effect = effect.next;
    }
    return effect;
  }
  function reconcile(state2, array, anchor, flags2, get_key) {
    var length = array.length;
    var items = state2.items;
    var current = skip_to_branch(state2.effect.first);
    var seen;
    var prev = null;
    var matched = [];
    var stashed = [];
    var value;
    var key;
    var effect;
    var i;
    for (i = 0; i < length; i += 1) {
      value = array[i];
      key = get_key(value, i);
      effect = /** @type {EachItem} */
      items.get(key).e;
      if (state2.outrogroups !== null) {
        for (const group of state2.outrogroups) {
          group.pending.delete(effect);
          group.done.delete(effect);
        }
      }
      if ((effect.f & INERT) !== 0) {
        resume_effect(effect);
      }
      if ((effect.f & EFFECT_OFFSCREEN) !== 0) {
        effect.f ^= EFFECT_OFFSCREEN;
        if (effect === current) {
          move(effect, null, anchor);
        } else {
          var next = prev ? prev.next : current;
          if (effect === state2.effect.last) {
            state2.effect.last = effect.prev;
          }
          if (effect.prev) effect.prev.next = effect.next;
          if (effect.next) effect.next.prev = effect.prev;
          link(state2, prev, effect);
          link(state2, effect, next);
          move(effect, next, anchor);
          prev = effect;
          matched = [];
          stashed = [];
          current = skip_to_branch(prev.next);
          continue;
        }
      }
      if (effect !== current) {
        if (seen !== void 0 && seen.has(effect)) {
          if (matched.length < stashed.length) {
            var start = stashed[0];
            var j;
            prev = start.prev;
            var a = matched[0];
            var b = matched[matched.length - 1];
            for (j = 0; j < matched.length; j += 1) {
              move(matched[j], start, anchor);
            }
            for (j = 0; j < stashed.length; j += 1) {
              seen.delete(stashed[j]);
            }
            link(state2, a.prev, b.next);
            link(state2, prev, a);
            link(state2, b, start);
            current = start;
            prev = b;
            i -= 1;
            matched = [];
            stashed = [];
          } else {
            seen.delete(effect);
            move(effect, current, anchor);
            link(state2, effect.prev, effect.next);
            link(state2, effect, prev === null ? state2.effect.first : prev.next);
            link(state2, prev, effect);
            prev = effect;
          }
          continue;
        }
        matched = [];
        stashed = [];
        while (current !== null && current !== effect) {
          (seen ??= /* @__PURE__ */ new Set()).add(current);
          stashed.push(current);
          current = skip_to_branch(current.next);
        }
        if (current === null) {
          continue;
        }
      }
      if ((effect.f & EFFECT_OFFSCREEN) === 0) {
        matched.push(effect);
      }
      prev = effect;
      current = skip_to_branch(effect.next);
    }
    if (state2.outrogroups !== null) {
      for (const group of state2.outrogroups) {
        if (group.pending.size === 0) {
          destroy_effects(state2, array_from(group.done));
          state2.outrogroups?.delete(group);
        }
      }
      if (state2.outrogroups.size === 0) {
        state2.outrogroups = null;
      }
    }
    if (current !== null || seen !== void 0) {
      var to_destroy = [];
      if (seen !== void 0) {
        for (effect of seen) {
          if ((effect.f & INERT) === 0) {
            to_destroy.push(effect);
          }
        }
      }
      while (current !== null) {
        if ((current.f & INERT) === 0 && current !== state2.fallback) {
          to_destroy.push(current);
        }
        current = skip_to_branch(current.next);
      }
      var destroy_length = to_destroy.length;
      if (destroy_length > 0) {
        var controlled_anchor = length === 0 ? anchor : null;
        pause_effects(state2, to_destroy, controlled_anchor);
      }
    }
  }
  function create_item(items, anchor, value, key, index2, render_fn, flags2, get_collection) {
    var v = (flags2 & EACH_ITEM_REACTIVE) !== 0 ? (flags2 & EACH_ITEM_IMMUTABLE) === 0 ? /* @__PURE__ */ mutable_source(value, false, false) : source(value) : null;
    var i = (flags2 & EACH_INDEX_REACTIVE) !== 0 ? source(index2) : null;
    return {
      v,
      i,
      e: branch(() => {
        render_fn(anchor, v ?? value, i ?? index2, get_collection);
        return () => {
          items.delete(key);
        };
      })
    };
  }
  function move(effect, next, anchor) {
    if (!effect.nodes) return;
    var node = effect.nodes.start;
    var end = effect.nodes.end;
    var dest = next && (next.f & EFFECT_OFFSCREEN) === 0 ? (
      /** @type {EffectNodes} */
      next.nodes.start
    ) : anchor;
    while (node !== null) {
      var next_node = (
        /** @type {TemplateNode} */
        /* @__PURE__ */ get_next_sibling(node)
      );
      dest.before(node);
      if (node === end) {
        return;
      }
      node = next_node;
    }
  }
  function link(state2, prev, next) {
    if (prev === null) {
      state2.effect.first = next;
    } else {
      prev.next = next;
    }
    if (next === null) {
      state2.effect.last = prev;
    } else {
      next.prev = prev;
    }
  }
  function to_class(value, hash, directives) {
    var classname = value == null ? "" : "" + value;
    {
      classname = classname ? classname + " " + hash : hash;
    }
    return classname === "" ? null : classname;
  }
  function set_class(dom, is_html, value, hash, prev_classes, next_classes) {
    var prev = dom.__className;
    if (prev !== value || prev === void 0) {
      var next_class_name = to_class(value, hash);
      {
        if (next_class_name == null) {
          dom.removeAttribute("class");
        } else {
          dom.className = next_class_name;
        }
      }
      dom.__className = value;
    }
    return next_classes;
  }
  const IS_CUSTOM_ELEMENT = /* @__PURE__ */ Symbol("is custom element");
  const IS_HTML = /* @__PURE__ */ Symbol("is html");
  function set_attribute(element, attribute, value, skip_warning) {
    var attributes = get_attributes(element);
    if (attributes[attribute] === (attributes[attribute] = value)) return;
    if (attribute === "loading") {
      element[LOADING_ATTR_SYMBOL] = value;
    }
    if (value == null) {
      element.removeAttribute(attribute);
    } else if (typeof value !== "string" && get_setters(element).includes(attribute)) {
      element[attribute] = value;
    } else {
      element.setAttribute(attribute, value);
    }
  }
  function set_custom_element_data(node, prop2, value) {
    var previous_reaction = active_reaction;
    var previous_effect = active_effect;
    set_active_reaction(null);
    set_active_effect(null);
    try {
      if (
        // `style` should use `set_attribute` rather than the setter
        prop2 !== "style" && // Don't compute setters for custom elements while they aren't registered yet,
        // because during their upgrade/instantiation they might add more setters.
        // Instead, fall back to a simple "an object, then set as property" heuristic.
        (setters_cache.has(node.getAttribute("is") || node.nodeName) || // customElements may not be available in browser extension contexts
        !customElements || customElements.get(node.getAttribute("is") || node.nodeName.toLowerCase()) ? get_setters(node).includes(prop2) : value && typeof value === "object")
      ) {
        node[prop2] = value;
      } else {
        set_attribute(node, prop2, value == null ? value : String(value));
      }
    } finally {
      set_active_reaction(previous_reaction);
      set_active_effect(previous_effect);
    }
  }
  function get_attributes(element) {
    return (
      /** @type {Record<string | symbol, unknown>} **/
      // @ts-expect-error
      element.__attributes ??= {
        [IS_CUSTOM_ELEMENT]: element.nodeName.includes("-"),
        [IS_HTML]: element.namespaceURI === NAMESPACE_HTML
      }
    );
  }
  var setters_cache = /* @__PURE__ */ new Map();
  function get_setters(element) {
    var cache_key = element.getAttribute("is") || element.nodeName;
    var setters = setters_cache.get(cache_key);
    if (setters) return setters;
    setters_cache.set(cache_key, setters = []);
    var descriptors;
    var proto = element;
    var element_proto = Element.prototype;
    while (element_proto !== proto) {
      descriptors = get_descriptors(proto);
      for (var key in descriptors) {
        if (descriptors[key].set) {
          setters.push(key);
        }
      }
      proto = get_prototype_of(proto);
    }
    return setters;
  }
  function init(immutable = false) {
    const context = (
      /** @type {ComponentContextLegacy} */
      component_context
    );
    const callbacks = context.l.u;
    if (!callbacks) return;
    let props = () => deep_read_state(context.s);
    if (immutable) {
      let version = 0;
      let prev = (
        /** @type {Record<string, any>} */
        {}
      );
      const d = /* @__PURE__ */ derived(() => {
        let changed = false;
        const props2 = context.s;
        for (const key in props2) {
          if (props2[key] !== prev[key]) {
            prev[key] = props2[key];
            changed = true;
          }
        }
        if (changed) version++;
        return version;
      });
      props = () => get(d);
    }
    if (callbacks.b.length) {
      user_pre_effect(() => {
        observe_all(context, props);
        run_all(callbacks.b);
      });
    }
    user_effect(() => {
      const fns = untrack(() => callbacks.m.map(run));
      return () => {
        for (const fn of fns) {
          if (typeof fn === "function") {
            fn();
          }
        }
      };
    });
    if (callbacks.a.length) {
      user_effect(() => {
        observe_all(context, props);
        run_all(callbacks.a);
      });
    }
  }
  function observe_all(context, props) {
    if (context.l.s) {
      for (const signal of context.l.s) get(signal);
    }
    props();
  }
  function prop(props, key, flags2, fallback) {
    var runes = !legacy_mode_flag || (flags2 & PROPS_IS_RUNES) !== 0;
    var bindable = (flags2 & PROPS_IS_BINDABLE) !== 0;
    var fallback_value = (
      /** @type {V} */
      fallback
    );
    var fallback_dirty = true;
    var get_fallback = () => {
      if (fallback_dirty) {
        fallback_dirty = false;
        fallback_value = /** @type {V} */
        fallback;
      }
      return fallback_value;
    };
    let setter;
    {
      var is_entry_props = STATE_SYMBOL in props || LEGACY_PROPS in props;
      setter = get_descriptor(props, key)?.set ?? (is_entry_props && key in props ? (v) => props[key] = v : void 0);
    }
    var initial_value;
    var is_store_sub = false;
    {
      [initial_value, is_store_sub] = capture_store_binding(() => (
        /** @type {V} */
        props[key]
      ));
    }
    var getter;
    if (runes) {
      getter = () => {
        var value = (
          /** @type {V} */
          props[key]
        );
        if (value === void 0) return get_fallback();
        fallback_dirty = true;
        return value;
      };
    } else {
      getter = () => {
        var value = (
          /** @type {V} */
          props[key]
        );
        if (value !== void 0) {
          fallback_value = /** @type {V} */
          void 0;
        }
        return value === void 0 ? fallback_value : value;
      };
    }
    if (runes && (flags2 & PROPS_IS_UPDATED) === 0) {
      return getter;
    }
    if (setter) {
      var legacy_parent = props.$$legacy;
      return (
        /** @type {() => V} */
        (function(value, mutation) {
          if (arguments.length > 0) {
            if (!runes || !mutation || legacy_parent || is_store_sub) {
              setter(mutation ? getter() : value);
            }
            return value;
          }
          return getter();
        })
      );
    }
    var overridden = false;
    var d = /* @__PURE__ */ derived_safe_equal(() => {
      overridden = false;
      return getter();
    });
    get(d);
    var parent_effect = (
      /** @type {Effect} */
      active_effect
    );
    return (
      /** @type {() => V} */
      (function(value, mutation) {
        if (arguments.length > 0) {
          const new_value = mutation ? get(d) : runes && bindable ? proxy(value) : value;
          set(d, new_value);
          overridden = true;
          if (fallback_value !== void 0) {
            fallback_value = new_value;
          }
          return value;
        }
        if (is_destroying_effect && overridden || (parent_effect.f & DESTROYED) !== 0) {
          return d.v;
        }
        return get(d);
      })
    );
  }
  function onMount(fn) {
    if (component_context === null) {
      lifecycle_outside_component();
    }
    if (legacy_mode_flag && component_context.l !== null) {
      init_update_callbacks(component_context).m.push(fn);
    } else {
      user_effect(() => {
        const cleanup = untrack(fn);
        if (typeof cleanup === "function") return (
          /** @type {() => void} */
          cleanup
        );
      });
    }
  }
  function onDestroy(fn) {
    if (component_context === null) {
      lifecycle_outside_component();
    }
    onMount(() => () => untrack(fn));
  }
  function init_update_callbacks(context) {
    var l = (
      /** @type {ComponentContextLegacy} */
      context.l
    );
    return l.u ??= { a: [], b: [], m: [] };
  }
  const PUBLIC_VERSION = "5";
  if (typeof window !== "undefined") {
    ((window.__svelte ??= {}).v ??= /* @__PURE__ */ new Set()).add(PUBLIC_VERSION);
  }
  enable_legacy_mode_flag();
  const Context = writable({
    beam: null
  });
  derived$1(Context, ($ctx) => $ctx.beam);
  var root_1 = /* @__PURE__ */ from_html(`<p class="placeholder svelte-1vjxqu">Loading servers...</p>`);
  var root_2 = /* @__PURE__ */ from_html(`<p class="error svelte-1vjxqu"> </p>`);
  var root_4 = /* @__PURE__ */ from_html(`<tr><td class="svelte-1vjxqu"> </td><td class="svelte-1vjxqu"> </td><td class="svelte-1vjxqu"> </td><td class="svelte-1vjxqu"> </td><td class="svelte-1vjxqu"><beam-btn>Check More Info</beam-btn></td></tr>`, 2);
  var root_7 = /* @__PURE__ */ from_html(`<div class="detail-row svelte-1vjxqu"><span class="detail-label svelte-1vjxqu">Error</span> <span class="detail-value error-text svelte-1vjxqu"> </span></div>`);
  var root_10 = /* @__PURE__ */ from_html(`<a target="_blank" rel="noopener noreferrer" class="svelte-1vjxqu"> </a>`);
  var root_9 = /* @__PURE__ */ from_html(`<tr><td class="svelte-1vjxqu"> </td><td class="detail-mono svelte-1vjxqu"> </td><td class="detail-mono svelte-1vjxqu"> </td><td class="svelte-1vjxqu"><span class="protocol-badge svelte-1vjxqu"> </span></td><td class="detail-mono svelte-1vjxqu"><!></td></tr>`);
  var root_8 = /* @__PURE__ */ from_html(`<div class="detail-section detail-section-full svelte-1vjxqu"><h5 class="svelte-1vjxqu">Ports</h5> <table class="inner-table svelte-1vjxqu"><thead><tr><th class="svelte-1vjxqu">Name</th><th class="svelte-1vjxqu">Internal</th><th class="svelte-1vjxqu">External</th><th class="svelte-1vjxqu">Protocol</th><th class="svelte-1vjxqu">Link</th></tr></thead><tbody></tbody></table></div>`);
  var root_12 = /* @__PURE__ */ from_html(`<div class="detail-section detail-section-full svelte-1vjxqu"><h5 class="svelte-1vjxqu">Location</h5> <div class="location-info svelte-1vjxqu"><span> </span> <span class="detail-muted svelte-1vjxqu"> </span></div></div>`);
  var root_14 = /* @__PURE__ */ from_html(`<tr><td class="detail-mono svelte-1vjxqu"> </td><td class="svelte-1vjxqu"> </td><td class="svelte-1vjxqu"> </td><td class="svelte-1vjxqu"> </td><td class="svelte-1vjxqu"> </td><td class="svelte-1vjxqu"> </td></tr>`);
  var root_13 = /* @__PURE__ */ from_html(`<div class="detail-section detail-section-full svelte-1vjxqu"><h5 class="svelte-1vjxqu"> </h5> <table class="inner-table svelte-1vjxqu"><thead><tr><th class="svelte-1vjxqu">Session ID</th><th class="svelte-1vjxqu">Status</th><th class="svelte-1vjxqu">Ready</th><th class="svelte-1vjxqu">Linked</th><th class="svelte-1vjxqu">Kind</th><th class="svelte-1vjxqu">Users</th></tr></thead><tbody></tbody></table></div>`);
  var root_16 = /* @__PURE__ */ from_html(`<span class="tag-pill svelte-1vjxqu"> </span>`);
  var root_15 = /* @__PURE__ */ from_html(`<div class="detail-section detail-section-full svelte-1vjxqu"><h5 class="svelte-1vjxqu">Tags</h5> <div class="tags-list svelte-1vjxqu"></div></div>`);
  var root_6 = /* @__PURE__ */ from_html(`<div class="details-grid svelte-1vjxqu"><div class="detail-section svelte-1vjxqu"><h5 class="svelte-1vjxqu">Status</h5> <div class="detail-row svelte-1vjxqu"><span class="detail-label svelte-1vjxqu">Running</span> <span> </span></div> <div class="detail-row svelte-1vjxqu"><span class="detail-label svelte-1vjxqu">Current</span> <span class="detail-value svelte-1vjxqu"> </span></div> <div class="detail-row svelte-1vjxqu"><span class="detail-label svelte-1vjxqu">Last</span> <span class="detail-value svelte-1vjxqu"> </span></div> <!></div> <div class="detail-section svelte-1vjxqu"><h5 class="svelte-1vjxqu">Application</h5> <div class="detail-row svelte-1vjxqu"><span class="detail-label svelte-1vjxqu">App</span> <span class="detail-value svelte-1vjxqu"> </span></div> <div class="detail-row svelte-1vjxqu"><span class="detail-label svelte-1vjxqu">Version</span> <span class="detail-value svelte-1vjxqu"> </span></div> <div class="detail-row svelte-1vjxqu"><span class="detail-label svelte-1vjxqu">FQDN</span> <span class="detail-value detail-mono svelte-1vjxqu"> </span></div> <div class="detail-row svelte-1vjxqu"><span class="detail-label svelte-1vjxqu">Public IP</span> <span class="detail-value detail-mono svelte-1vjxqu"> </span></div></div> <div class="detail-section svelte-1vjxqu"><h5 class="svelte-1vjxqu">Timing</h5> <div class="detail-row svelte-1vjxqu"><span class="detail-label svelte-1vjxqu">Started</span> <span class="detail-value svelte-1vjxqu"> </span></div> <div class="detail-row svelte-1vjxqu"><span class="detail-label svelte-1vjxqu">Elapsed</span> <span class="detail-value svelte-1vjxqu"> </span></div> <div class="detail-row svelte-1vjxqu"><span class="detail-label svelte-1vjxqu">Max Duration</span> <span class="detail-value svelte-1vjxqu"> </span></div> <div class="detail-row svelte-1vjxqu"><span class="detail-label svelte-1vjxqu">Whitelisting</span> <span class="detail-value svelte-1vjxqu"> </span></div></div> <div class="detail-section svelte-1vjxqu"><h5 class="svelte-1vjxqu">Capacity</h5> <div class="detail-row svelte-1vjxqu"><span class="detail-label svelte-1vjxqu">Sockets Used</span> <span class="detail-value svelte-1vjxqu"> </span></div></div></div> <!> <!> <!> <!>`, 1);
  var root_17 = /* @__PURE__ */ from_html(`<p class="placeholder svelte-1vjxqu">No additional details available for this server.</p>`);
  var root_5 = /* @__PURE__ */ from_html(`<div class="details-panel svelte-1vjxqu"><div class="details-header svelte-1vjxqu"><h4 class="svelte-1vjxqu">Server Details</h4> <span class="request-id-badge svelte-1vjxqu"> </span></div> <!></div>`);
  var root_3 = /* @__PURE__ */ from_html(`<div class="table-wrap svelte-1vjxqu"><table class="svelte-1vjxqu"><thead><tr><th class="svelte-1vjxqu">Request ID</th><th class="svelte-1vjxqu">FQDN</th><th class="svelte-1vjxqu">Running</th><th class="svelte-1vjxqu">State</th><th class="svelte-1vjxqu">Action</th></tr></thead><tbody></tbody></table></div> <!>`, 1);
  var root_18 = /* @__PURE__ */ from_html(`<p class="placeholder svelte-1vjxqu">Load servers to see running instances and statuses.</p>`);
  var root = /* @__PURE__ */ from_html(`<beam-card><beam-card-title>Edgegap Dedicated Servers</beam-card-title> <!> <!> <!></beam-card>`, 2);
  function EdgegapServers($$anchor, $$props) {
    push($$props, false);
    let loading = /* @__PURE__ */ mutable_source(false);
    let error = /* @__PURE__ */ mutable_source("");
    let apiToken = "";
    let deployments = /* @__PURE__ */ mutable_source([]);
    let deploymentDetails = /* @__PURE__ */ mutable_source({});
    let selectedRequestId = /* @__PURE__ */ mutable_source(null);
    let refreshInterval = null;
    async function getApiToken() {
      return "";
    }
    async function authHeaderValue() {
      if (!apiToken) {
        apiToken = await getApiToken();
      }
      return apiToken.trim().toLowerCase().startsWith("token ") ? apiToken.trim() : `token ${apiToken.trim()}`;
    }
    async function edgegapGet(path) {
      const response = await fetch(`https://api.edgegap.com${path}`, {
        method: "GET",
        headers: {
          authorization: await authHeaderValue(),
          accept: "application/json"
        }
      });
      if (!response.ok) {
        let message = `Request failed (${response.status})`;
        try {
          const payload = await response.json();
          message = payload?.message || payload?.error || message;
        } catch (_) {
        }
        throw new Error(message);
      }
      return response.json();
    }
    async function loadDeployments() {
      set(loading, true);
      set(error, "");
      try {
        if (!apiToken.trim()) {
          apiToken = await getApiToken();
        }
        const listResponse = await edgegapGet("/v1/deployments");
        const newDeployments = Array.isArray(listResponse?.data) ? listResponse.data : [];
        const newDetails = {};
        await Promise.all(newDeployments.map(async (deployment) => {
          if (!deployment?.request_id) return;
          try {
            newDetails[deployment.request_id] = await edgegapGet(`/v1/status/${deployment.request_id}`);
          } catch (_) {
            newDetails[deployment.request_id] = null;
          }
        }));
        set(deployments, newDeployments);
        set(deploymentDetails, newDetails);
        if (get(selectedRequestId) && !newDetails.hasOwnProperty(get(selectedRequestId))) {
          set(selectedRequestId, null);
        }
      } catch (err) {
        console.error("Failed to load Edgegap deployments:", err);
        set(error, err?.message || "Failed to load deployments.");
      } finally {
        set(loading, false);
      }
    }
    onMount(() => {
      loadDeployments();
      refreshInterval = setInterval(loadDeployments, 1e4);
    });
    onDestroy(() => {
      clearInterval(refreshInterval);
    });
    function showMoreInfo(requestId) {
      set(selectedRequestId, get(selectedRequestId) === requestId ? null : requestId);
    }
    function runningLabel(deployment) {
      const details = get(deploymentDetails)[deployment.request_id];
      if (details?.running === true) return "Running";
      if (details?.running === false) return "Stopped";
      if (deployment?.ready === true) return "Running";
      if (deployment?.ready === false) return "Starting";
      return "Unknown";
    }
    function stateLabel(deployment) {
      const details = get(deploymentDetails)[deployment.request_id];
      return details?.current_status || details?.last_status || (deployment?.ready ? "Status.READY" : "Status.UNKNOWN");
    }
    init();
    var beam_card = root();
    var beam_card_title = child(beam_card);
    var node = sibling(beam_card_title, 2);
    {
      var consequent = ($$anchor2) => {
        var p = root_1();
        append($$anchor2, p);
      };
      if_block(node, ($$render) => {
        if (get(loading) && get(deployments).length === 0) $$render(consequent);
      });
    }
    var node_1 = sibling(node, 2);
    {
      var consequent_1 = ($$anchor2) => {
        var p_1 = root_2();
        var text2 = child(p_1);
        template_effect(() => set_text(text2, get(error)));
        append($$anchor2, p_1);
      };
      if_block(node_1, ($$render) => {
        if (get(error)) $$render(consequent_1);
      });
    }
    var node_2 = sibling(node_1, 2);
    {
      var consequent_10 = ($$anchor2) => {
        var fragment = root_3();
        var div = first_child(fragment);
        var table = child(div);
        var tbody = sibling(child(table));
        each(tbody, 5, () => get(deployments), index, ($$anchor3, deployment) => {
          var tr = root_4();
          var td = child(tr);
          var text_1 = child(td);
          var td_1 = sibling(td);
          var text_2 = child(td_1);
          var td_2 = sibling(td_1);
          var text_3 = child(td_2);
          var td_3 = sibling(td_2);
          var text_4 = child(td_3);
          var td_4 = sibling(td_3);
          var beam_btn = child(td_4);
          set_custom_element_data(beam_btn, "role", "button");
          set_custom_element_data(beam_btn, "tabindex", "0");
          template_effect(
            ($0, $1) => {
              set_text(text_1, get(deployment).request_id);
              set_text(text_2, get(deployment).fqdn || "N/A");
              set_text(text_3, $0);
              set_text(text_4, $1);
            },
            [
              () => runningLabel(get(deployment)),
              () => stateLabel(get(deployment))
            ]
          );
          event("click", beam_btn, () => showMoreInfo(get(deployment).request_id));
          event("keydown", beam_btn, (event2) => (event2.key === "Enter" || event2.key === " ") && showMoreInfo(get(deployment).request_id));
          append($$anchor3, tr);
        });
        var node_3 = sibling(div, 2);
        {
          var consequent_9 = ($$anchor3) => {
            var div_1 = root_5();
            var div_2 = child(div_1);
            var span = sibling(child(div_2), 2);
            var text_5 = child(span);
            var node_4 = sibling(div_2, 2);
            {
              var consequent_8 = ($$anchor4) => {
                const d = /* @__PURE__ */ derived_safe_equal(() => get(deploymentDetails)[get(selectedRequestId)]);
                var fragment_1 = root_6();
                var div_3 = first_child(fragment_1);
                var div_4 = child(div_3);
                var div_5 = sibling(child(div_4), 2);
                var span_1 = sibling(child(div_5), 2);
                var text_6 = child(span_1);
                var div_6 = sibling(div_5, 2);
                var span_2 = sibling(child(div_6), 2);
                var text_7 = child(span_2);
                var div_7 = sibling(div_6, 2);
                var span_3 = sibling(child(div_7), 2);
                var text_8 = child(span_3);
                var node_5 = sibling(div_7, 2);
                {
                  var consequent_2 = ($$anchor5) => {
                    var div_8 = root_7();
                    var span_4 = sibling(child(div_8), 2);
                    var text_9 = child(span_4);
                    template_effect(() => set_text(text_9, get(d).error_detail || "Unknown error"));
                    append($$anchor5, div_8);
                  };
                  if_block(node_5, ($$render) => {
                    if (get(d).error) $$render(consequent_2);
                  });
                }
                var div_9 = sibling(div_4, 2);
                var div_10 = sibling(child(div_9), 2);
                var span_5 = sibling(child(div_10), 2);
                var text_10 = child(span_5);
                var div_11 = sibling(div_10, 2);
                var span_6 = sibling(child(div_11), 2);
                var text_11 = child(span_6);
                var div_12 = sibling(div_11, 2);
                var span_7 = sibling(child(div_12), 2);
                var text_12 = child(span_7);
                var div_13 = sibling(div_12, 2);
                var span_8 = sibling(child(div_13), 2);
                var text_13 = child(span_8);
                var div_14 = sibling(div_9, 2);
                var div_15 = sibling(child(div_14), 2);
                var span_9 = sibling(child(div_15), 2);
                var text_14 = child(span_9);
                var div_16 = sibling(div_15, 2);
                var span_10 = sibling(child(div_16), 2);
                var text_15 = child(span_10);
                var div_17 = sibling(div_16, 2);
                var span_11 = sibling(child(div_17), 2);
                var text_16 = child(span_11);
                var div_18 = sibling(div_17, 2);
                var span_12 = sibling(child(div_18), 2);
                var text_17 = child(span_12);
                var div_19 = sibling(div_14, 2);
                var div_20 = sibling(child(div_19), 2);
                var span_13 = sibling(child(div_20), 2);
                var text_18 = child(span_13);
                var node_6 = sibling(div_3, 2);
                {
                  var consequent_4 = ($$anchor5) => {
                    var div_21 = root_8();
                    var table_1 = sibling(child(div_21), 2);
                    var tbody_1 = sibling(child(table_1));
                    each(tbody_1, 5, () => Object.values(get(d).ports), index, ($$anchor6, port) => {
                      var tr_1 = root_9();
                      var td_5 = child(tr_1);
                      var text_19 = child(td_5);
                      var td_6 = sibling(td_5);
                      var text_20 = child(td_6);
                      var td_7 = sibling(td_6);
                      var text_21 = child(td_7);
                      var td_8 = sibling(td_7);
                      var span_14 = child(td_8);
                      var text_22 = child(span_14);
                      var td_9 = sibling(td_8);
                      var node_7 = child(td_9);
                      {
                        var consequent_3 = ($$anchor7) => {
                          var a = root_10();
                          var text_23 = child(a);
                          template_effect(() => {
                            set_attribute(a, "href", get(port).link);
                            set_text(text_23, get(port).link);
                          });
                          append($$anchor7, a);
                        };
                        var alternate = ($$anchor7) => {
                          var text_24 = text("N/A");
                          append($$anchor7, text_24);
                        };
                        if_block(node_7, ($$render) => {
                          if (get(port).link) $$render(consequent_3);
                          else $$render(alternate, -1);
                        });
                      }
                      template_effect(() => {
                        set_text(text_19, get(port).name);
                        set_text(text_20, get(port).internal);
                        set_text(text_21, get(port).external);
                        set_text(text_22, get(port).protocol);
                      });
                      append($$anchor6, tr_1);
                    });
                    append($$anchor5, div_21);
                  };
                  var d_1 = /* @__PURE__ */ user_derived(() => get(d).ports && Object.keys(get(d).ports).length > 0);
                  if_block(node_6, ($$render) => {
                    if (get(d_1)) $$render(consequent_4);
                  });
                }
                var node_8 = sibling(node_6, 2);
                {
                  var consequent_5 = ($$anchor5) => {
                    var div_22 = root_12();
                    var div_23 = sibling(child(div_22), 2);
                    var span_15 = child(div_23);
                    var text_25 = child(span_15);
                    var span_16 = sibling(span_15, 2);
                    var text_26 = child(span_16);
                    template_effect(
                      ($0, $1) => {
                        set_text(text_25, $0);
                        set_text(text_26, $1);
                      },
                      [
                        () => [
                          get(d).location.city,
                          get(d).location.administrative_division,
                          get(d).location.country
                        ].filter(Boolean).join(", "),
                        () => [get(d).location.continent, get(d).location.timezone].filter(Boolean).join(" · ")
                      ]
                    );
                    append($$anchor5, div_22);
                  };
                  if_block(node_8, ($$render) => {
                    if (get(d).location) $$render(consequent_5);
                  });
                }
                var node_9 = sibling(node_8, 2);
                {
                  var consequent_6 = ($$anchor5) => {
                    var div_24 = root_13();
                    var h5 = child(div_24);
                    var text_27 = child(h5);
                    var table_2 = sibling(h5, 2);
                    var tbody_2 = sibling(child(table_2));
                    each(tbody_2, 5, () => get(d).sessions, index, ($$anchor6, session) => {
                      var tr_2 = root_14();
                      var td_10 = child(tr_2);
                      var text_28 = child(td_10);
                      var td_11 = sibling(td_10);
                      var text_29 = child(td_11);
                      var td_12 = sibling(td_11);
                      var text_30 = child(td_12);
                      var td_13 = sibling(td_12);
                      var text_31 = child(td_13);
                      var td_14 = sibling(td_13);
                      var text_32 = child(td_14);
                      var td_15 = sibling(td_14);
                      var text_33 = child(td_15);
                      template_effect(() => {
                        set_text(text_28, get(session).session_id);
                        set_text(text_29, get(session).status);
                        set_text(text_30, get(session).ready ? "Yes" : "No");
                        set_text(text_31, get(session).linked ? "Yes" : "No");
                        set_text(text_32, get(session).kind);
                        set_text(text_33, get(session).user_count);
                      });
                      append($$anchor6, tr_2);
                    });
                    template_effect(() => set_text(text_27, `Sessions (${get(d).sessions.length ?? ""})`));
                    append($$anchor5, div_24);
                  };
                  if_block(node_9, ($$render) => {
                    if (get(d).sessions && get(d).sessions.length > 0) $$render(consequent_6);
                  });
                }
                var node_10 = sibling(node_9, 2);
                {
                  var consequent_7 = ($$anchor5) => {
                    var div_25 = root_15();
                    var div_26 = sibling(child(div_25), 2);
                    each(div_26, 5, () => get(d).tags, index, ($$anchor6, tag) => {
                      var span_17 = root_16();
                      var text_34 = child(span_17);
                      template_effect(() => set_text(text_34, get(tag)));
                      append($$anchor6, span_17);
                    });
                    append($$anchor5, div_25);
                  };
                  if_block(node_10, ($$render) => {
                    if (get(d).tags && get(d).tags.length > 0) $$render(consequent_7);
                  });
                }
                template_effect(() => {
                  set_class(span_1, 1, `status-badge ${get(d).running ? "status-running" : "status-stopped"}`, "svelte-1vjxqu");
                  set_text(text_6, get(d).running ? "Running" : "Stopped");
                  set_text(text_7, get(d).current_status || "N/A");
                  set_text(text_8, get(d).last_status || "N/A");
                  set_text(text_10, get(d).app_name || "N/A");
                  set_text(text_11, get(d).app_version || "N/A");
                  set_text(text_12, get(d).fqdn || "N/A");
                  set_text(text_13, get(d).public_ip || "N/A");
                  set_text(text_14, get(d).start_time || "N/A");
                  set_text(text_15, get(d).elapsed_time != null ? `${get(d).elapsed_time}s` : "N/A");
                  set_text(text_16, get(d).max_duration != null ? `${get(d).max_duration}h` : "N/A");
                  set_text(text_17, get(d).whitelisting_active ? "Active" : "Inactive");
                  set_text(text_18, `${get(d).sockets_usage ?? "N/A" ?? ""} / ${get(d).sockets ?? "N/A" ?? ""}`);
                });
                append($$anchor4, fragment_1);
              };
              var alternate_1 = ($$anchor4) => {
                var p_2 = root_17();
                append($$anchor4, p_2);
              };
              if_block(node_4, ($$render) => {
                if (get(deploymentDetails)[get(selectedRequestId)]) $$render(consequent_8);
                else $$render(alternate_1, -1);
              });
            }
            template_effect(() => set_text(text_5, get(selectedRequestId)));
            append($$anchor3, div_1);
          };
          if_block(node_3, ($$render) => {
            if (get(selectedRequestId)) $$render(consequent_9);
          });
        }
        append($$anchor2, fragment);
      };
      var consequent_11 = ($$anchor2) => {
        var p_3 = root_18();
        append($$anchor2, p_3);
      };
      if_block(node_2, ($$render) => {
        if (get(deployments).length > 0) $$render(consequent_10);
        else if (!get(loading)) $$render(consequent_11, 1);
      });
    }
    append($$anchor, beam_card);
    pop();
  }
  function App($$anchor, $$props) {
    push($$props, false);
    let context = prop($$props, "context", 8);
    legacy_pre_effect(() => deep_read_state(context()), () => {
      Context.set(context());
    });
    legacy_pre_effect_reset();
    init();
    EdgegapServers($$anchor, {});
    pop();
  }
  const APP_NAMESPACE = "edgegap_server_extensions";
  window[APP_NAMESPACE] = {
    mount: (targetElement, props) => {
      return mount(App, {
        target: targetElement,
        props
      });
    },
    unmount: (appInstance) => {
      unmount(appInstance);
    }
  };
})();
