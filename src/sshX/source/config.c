/*
* config.c - the platform-independent parts of the PuTTY
* configuration box.
*/

#include <assert.h>
#include <stdlib.h>

#include "putty.h"
#include "dialog.h"
#include "storage.h"

#define PRINTER_DISABLED_STRING "�� (��ֹ��ӡ)"

static void protocolbuttons_handler(union control *ctrl, void *dlg,
									void *data, int event)
{
    int button, defport;
    Config *cfg = (Config *)data;
    /*
	* This function works just like the standard radio-button
	* handler, except that it also has to change the setting of
	* the port box. We expect the context parameter to point at
	* the `union control' structure for the port box.
	*/
    if (event == EVENT_REFRESH) {
		for (button = 0; button < ctrl->radio.nbuttons; button++)
			if (cfg->protocol == ctrl->radio.buttondata[button].i)
				break;
			/* We expected that `break' to happen, in all circumstances. */
			assert(button < ctrl->radio.nbuttons);
			dlg_radiobutton_set(ctrl, dlg, button);
    } else if (event == EVENT_VALCHANGE) {
		int oldproto = cfg->protocol;
		button = dlg_radiobutton_get(ctrl, dlg);
		assert(button >= 0 && button < ctrl->radio.nbuttons);
		cfg->protocol = ctrl->radio.buttondata[button].i;
		if (oldproto != cfg->protocol) {
			defport = -1;
			switch (cfg->protocol) {
			case PROT_SSH: defport = 22; break;
			case PROT_TELNET: defport = 23; break;
			case PROT_RLOGIN: defport = 513; break;
			}
			if (defport > 0 && cfg->port != defport) {
				cfg->port = defport;
				dlg_refresh((union control *)ctrl->radio.context.p, dlg);
			}
		}
    }
}

static void loggingbuttons_handler(union control *ctrl, void *dlg,
								   void *data, int event)
{
    int button;
    Config *cfg = (Config *)data;
    /* This function works just like the standard radio-button handler,
	* but it has to fall back to "no logging" in situations where the
	* configured logging type isn't applicable.
	*/
    if (event == EVENT_REFRESH) {
        for (button = 0; button < ctrl->radio.nbuttons; button++)
            if (cfg->logtype == ctrl->radio.buttondata[button].i)
				break;
			
			/* We fell off the end, so we lack the configured logging type */
			if (button == ctrl->radio.nbuttons) {
				button=0;
				cfg->logtype=LGTYP_NONE;
			}
			dlg_radiobutton_set(ctrl, dlg, button);
    } else if (event == EVENT_VALCHANGE) {
        button = dlg_radiobutton_get(ctrl, dlg);
        assert(button >= 0 && button < ctrl->radio.nbuttons);
        cfg->logtype = ctrl->radio.buttondata[button].i;
    }
}

static void numeric_keypad_handler(union control *ctrl, void *dlg,
								   void *data, int event)
{
    int button;
    Config *cfg = (Config *)data;
    /*
	* This function works much like the standard radio button
	* handler, but it has to handle two fields in Config.
	*/
    if (event == EVENT_REFRESH) {
		if (cfg->nethack_keypad)
			button = 2;
		else if (cfg->app_keypad)
			button = 1;
		else
			button = 0;
		assert(button < ctrl->radio.nbuttons);
		dlg_radiobutton_set(ctrl, dlg, button);
    } else if (event == EVENT_VALCHANGE) {
		button = dlg_radiobutton_get(ctrl, dlg);
		assert(button >= 0 && button < ctrl->radio.nbuttons);
		if (button == 2) {
			cfg->app_keypad = FALSE;
			cfg->nethack_keypad = TRUE;
		} else {
			cfg->app_keypad = (button != 0);
			cfg->nethack_keypad = FALSE;
		}
    }
}

static void cipherlist_handler(union control *ctrl, void *dlg,
							   void *data, int event)
{
    Config *cfg = (Config *)data;
    if (event == EVENT_REFRESH) {
		int i;
		
		static const struct { char *s; int c; } ciphers[] = {
			{ "3DES",			CIPHER_3DES },
			{ "Blowfish",		CIPHER_BLOWFISH },
			{ "DES",			CIPHER_DES },
			{ "AES (ֻ�� SSH-2)",	CIPHER_AES },
			{ "-- ����Ϊ����ѡ�� --",	CIPHER_WARN }
		};
		
		/* Set up the "selected ciphers" box. */
		/* (cipherlist assumed to contain all ciphers) */
		dlg_update_start(ctrl, dlg);
		dlg_listbox_clear(ctrl, dlg);
		for (i = 0; i < CIPHER_MAX; i++) {
			int c = cfg->ssh_cipherlist[i];
			int j;
			char *cstr = NULL;
			for (j = 0; j < (sizeof ciphers) / (sizeof ciphers[0]); j++) {
				if (ciphers[j].c == c) {
					cstr = ciphers[j].s;
					break;
				}
			}
			dlg_listbox_addwithid(ctrl, dlg, cstr, c);
		}
		dlg_update_done(ctrl, dlg);
		
    } else if (event == EVENT_VALCHANGE) {
		int i;
		
		/* Update array to match the list box. */
		for (i=0; i < CIPHER_MAX; i++)
			cfg->ssh_cipherlist[i] = dlg_listbox_getid(ctrl, dlg, i);
		
    }
}

static void kexlist_handler(union control *ctrl, void *dlg,
							void *data, int event)
{
    Config *cfg = (Config *)data;
    if (event == EVENT_REFRESH) {
		int i;
		
		static const struct { char *s; int k; } kexes[] = {
			{ "Diffie-Hellman group 1",		KEX_DHGROUP1 },
			{ "Diffie-Hellman group 14",	KEX_DHGROUP14 },
			{ "Diffie-Hellman group exchange",	KEX_DHGEX },
			{ "-- ����Ϊ����ѡ�� --",		KEX_WARN }
		};
		
		/* Set up the "kex preference" box. */
		/* (kexlist assumed to contain all algorithms) */
		dlg_update_start(ctrl, dlg);
		dlg_listbox_clear(ctrl, dlg);
		for (i = 0; i < KEX_MAX; i++) {
			int k = cfg->ssh_kexlist[i];
			int j;
			char *kstr = NULL;
			for (j = 0; j < (sizeof kexes) / (sizeof kexes[0]); j++) {
				if (kexes[j].k == k) {
					kstr = kexes[j].s;
					break;
				}
			}
			dlg_listbox_addwithid(ctrl, dlg, kstr, k);
		}
		dlg_update_done(ctrl, dlg);
		
    } else if (event == EVENT_VALCHANGE) {
		int i;
		
		/* Update array to match the list box. */
		for (i=0; i < KEX_MAX; i++)
			cfg->ssh_kexlist[i] = dlg_listbox_getid(ctrl, dlg, i);
		
    }
}

static void printerbox_handler(union control *ctrl, void *dlg,
							   void *data, int event)
{
    Config *cfg = (Config *)data;
    if (event == EVENT_REFRESH) {
		int nprinters, i;
		printer_enum *pe;
		
		dlg_update_start(ctrl, dlg);
		/*
		* Some backends may wish to disable the drop-down list on
		* this edit box. Be prepared for this.
		*/
		if (ctrl->editbox.has_list) {
			dlg_listbox_clear(ctrl, dlg);
			dlg_listbox_add(ctrl, dlg, PRINTER_DISABLED_STRING);
			pe = printer_start_enum(&nprinters);
			for (i = 0; i < nprinters; i++)
				dlg_listbox_add(ctrl, dlg, printer_get_name(pe, i));
			printer_finish_enum(pe);
		}
		dlg_editbox_set(ctrl, dlg,
			(*cfg->printer ? cfg->printer :
		PRINTER_DISABLED_STRING));
		dlg_update_done(ctrl, dlg);
    } else if (event == EVENT_VALCHANGE) {
		dlg_editbox_get(ctrl, dlg, cfg->printer, sizeof(cfg->printer));
		if (!strcmp(cfg->printer, PRINTER_DISABLED_STRING))
			*cfg->printer = '\0';
    }
}

static void codepage_handler(union control *ctrl, void *dlg,
							 void *data, int event)
{
    Config *cfg = (Config *)data;
    if (event == EVENT_REFRESH) {
		int i;
		const char *cp;
		dlg_update_start(ctrl, dlg);
		strcpy(cfg->line_codepage,
			cp_name(decode_codepage(cfg->line_codepage)));
		dlg_listbox_clear(ctrl, dlg);
		for (i = 0; (cp = cp_enumerate(i)) != NULL; i++)
			dlg_listbox_add(ctrl, dlg, cp);
		dlg_editbox_set(ctrl, dlg, cfg->line_codepage);
		dlg_update_done(ctrl, dlg);
    } else if (event == EVENT_VALCHANGE) {
		dlg_editbox_get(ctrl, dlg, cfg->line_codepage,
			sizeof(cfg->line_codepage));
		strcpy(cfg->line_codepage,
			cp_name(decode_codepage(cfg->line_codepage)));
    }
}

static void sshbug_handler(union control *ctrl, void *dlg,
						   void *data, int event)
{
    if (event == EVENT_REFRESH) {
		dlg_update_start(ctrl, dlg);
		dlg_listbox_clear(ctrl, dlg);
		dlg_listbox_addwithid(ctrl, dlg, "�Զ�", AUTO);
		dlg_listbox_addwithid(ctrl, dlg, "��", FORCE_OFF);
		dlg_listbox_addwithid(ctrl, dlg, "��", FORCE_ON);
		switch (*(int *)ATOFFSET(data, ctrl->listbox.context.i)) {
		case AUTO:      dlg_listbox_select(ctrl, dlg, 0); break;
		case FORCE_OFF: dlg_listbox_select(ctrl, dlg, 1); break;
		case FORCE_ON:  dlg_listbox_select(ctrl, dlg, 2); break;
		}
		dlg_update_done(ctrl, dlg);
    } else if (event == EVENT_SELCHANGE) {
		int i = dlg_listbox_index(ctrl, dlg);
		if (i < 0)
			i = AUTO;
		else
			i = dlg_listbox_getid(ctrl, dlg, i);
		*(int *)ATOFFSET(data, ctrl->listbox.context.i) = i;
    }
}

#define SAVEDSESSION_LEN 2048

struct sessionsaver_data {
    union control *editbox, *listbox, *loadbutton, *savebutton, *delbutton;
    union control *okbutton, *cancelbutton;
    struct sesslist *sesslist;
    int midsession;
};

/* 
* Helper function to load the session selected in the list box, if
* any, as this is done in more than one place below. Returns 0 for
* failure.
*/
static int load_selected_session(struct sessionsaver_data *ssd,
								 char *savedsession,
								 void *dlg, Config *cfg)
{
    int i = dlg_listbox_index(ssd->listbox, dlg);
    int isdef;
    if (i < 0) {
		dlg_beep(dlg);
		return 0;
    }
    isdef = !strcmp(ssd->sesslist->sessions[i], "Ĭ������");
    load_settings(ssd->sesslist->sessions[i], !isdef, cfg);
    if (!isdef) {
		strncpy(savedsession, ssd->sesslist->sessions[i],
			SAVEDSESSION_LEN);
		savedsession[SAVEDSESSION_LEN-1] = '\0';
    } else {
		savedsession[0] = '\0';
    }
    dlg_refresh(NULL, dlg);
    /* Restore the selection, which might have been clobbered by
	* changing the value of the edit box. */
    dlg_listbox_select(ssd->listbox, dlg, i);
    return 1;
}

static void sessionsaver_handler(union control *ctrl, void *dlg,
								 void *data, int event)
{
    Config *cfg = (Config *)data;
    struct sessionsaver_data *ssd =
		(struct sessionsaver_data *)ctrl->generic.context.p;
    char *savedsession;
	
    /*
	* The first time we're called in a new dialog, we must
	* allocate space to store the current contents of the saved
	* session edit box (since it must persist even when we switch
	* panels, but is not part of the Config).
	*/
    if (!ssd->editbox) {
        savedsession = NULL;
    } else if (!dlg_get_privdata(ssd->editbox, dlg)) {
		savedsession = (char *)
			dlg_alloc_privdata(ssd->editbox, dlg, SAVEDSESSION_LEN);
		savedsession[0] = '\0';
    } else {
		savedsession = dlg_get_privdata(ssd->editbox, dlg);
    }
	
    if (event == EVENT_REFRESH) {
		if (ctrl == ssd->editbox) {
			dlg_editbox_set(ctrl, dlg, savedsession);
		} else if (ctrl == ssd->listbox) {
			int i;
			dlg_update_start(ctrl, dlg);
			dlg_listbox_clear(ctrl, dlg);
			for (i = 0; i < ssd->sesslist->nsessions; i++)
				dlg_listbox_add(ctrl, dlg, ssd->sesslist->sessions[i]);
			dlg_update_done(ctrl, dlg);
		}
    } else if (event == EVENT_VALCHANGE) {
		if (ctrl == ssd->editbox) {
			dlg_editbox_get(ctrl, dlg, savedsession,
				SAVEDSESSION_LEN);
		}
    } else if (event == EVENT_ACTION) {
		if (!ssd->midsession &&
			(ctrl == ssd->listbox ||
			(ssd->loadbutton && ctrl == ssd->loadbutton))) {
			/*
			* The user has double-clicked a session, or hit Load.
			* We must load the selected session, and then
			* terminate the configuration dialog _if_ there was a
			* double-click on the list box _and_ that session
			* contains a hostname.
			*/
			if (load_selected_session(ssd, savedsession, dlg, cfg) &&
				(ctrl == ssd->listbox && cfg->host[0])) {
				dlg_end(dlg, 1);       /* it's all over, and succeeded */
			}
		} else if (ctrl == ssd->savebutton) {
			int isdef = !strcmp(savedsession, "Ĭ������");
			if (!savedsession[0]) {
				int i = dlg_listbox_index(ssd->listbox, dlg);
				if (i < 0) {
					dlg_beep(dlg);
					return;
				}
				isdef = !strcmp(ssd->sesslist->sessions[i], "Ĭ������");
				if (!isdef) {
					strncpy(savedsession, ssd->sesslist->sessions[i],
						SAVEDSESSION_LEN);
					savedsession[SAVEDSESSION_LEN-1] = '\0';
				} else {
					savedsession[0] = '\0';
				}
			}
            {
                char *errmsg = save_settings(savedsession, !isdef, cfg);
                if (errmsg) {
                    dlg_error_msg(dlg, errmsg);
                    sfree(errmsg);
                }
            }
			get_sesslist(ssd->sesslist, FALSE);
			get_sesslist(ssd->sesslist, TRUE);
			dlg_refresh(ssd->editbox, dlg);
			dlg_refresh(ssd->listbox, dlg);
		} else if (!ssd->midsession &&
			ssd->delbutton && ctrl == ssd->delbutton) {
			int i = dlg_listbox_index(ssd->listbox, dlg);
			if (i <= 0) {
				dlg_beep(dlg);
			} else {
				del_settings(ssd->sesslist->sessions[i]);
				get_sesslist(ssd->sesslist, FALSE);
				get_sesslist(ssd->sesslist, TRUE);
				dlg_refresh(ssd->listbox, dlg);
			}
		} else if (ctrl == ssd->okbutton) {
            if (ssd->midsession) {
                /* In a mid-session Change Settings, Apply is always OK. */
				dlg_end(dlg, 1);
                return;
            }
			/*
			* Annoying special case. If the `Open' button is
			* pressed while no host name is currently set, _and_
			* the session list previously had the focus, _and_
			* there was a session selected in that which had a
			* valid host name in it, then load it and go.
			*/
			if (dlg_last_focused(ctrl, dlg) == ssd->listbox && !*cfg->host) {
				Config cfg2;
				if (!load_selected_session(ssd, savedsession, dlg, &cfg2)) {
					dlg_beep(dlg);
					return;
				}
				/* If at this point we have a valid session, go! */
				if (*cfg2.host) {
					*cfg = cfg2;       /* structure copy */
					cfg->remote_cmd_ptr = NULL;
					dlg_end(dlg, 1);
				} else
					dlg_beep(dlg);
                return;
			}
			
			/*
			* Otherwise, do the normal thing: if we have a valid
			* session, get going.
			*/
			if (*cfg->host) {
				dlg_end(dlg, 1);
			} else
				dlg_beep(dlg);
		} else if (ctrl == ssd->cancelbutton) {
			dlg_end(dlg, 0);
		}
    }
}

struct charclass_data {
    union control *listbox, *editbox, *button;
};

static void charclass_handler(union control *ctrl, void *dlg,
							  void *data, int event)
{
    Config *cfg = (Config *)data;
    struct charclass_data *ccd =
		(struct charclass_data *)ctrl->generic.context.p;
	
    if (event == EVENT_REFRESH) {
		if (ctrl == ccd->listbox) {
			int i;
			dlg_update_start(ctrl, dlg);
			dlg_listbox_clear(ctrl, dlg);
			for (i = 0; i < 128; i++) {
				char str[100];
				sprintf(str, "%d\t(0x%02X)\t%c\t%d", i, i,
					(i >= 0x21 && i != 0x7F) ? i : ' ', cfg->wordness[i]);
				dlg_listbox_add(ctrl, dlg, str);
			}
			dlg_update_done(ctrl, dlg);
		}
    } else if (event == EVENT_ACTION) {
		if (ctrl == ccd->button) {
			char str[100];
			int i, n;
			dlg_editbox_get(ccd->editbox, dlg, str, sizeof(str));
			n = atoi(str);
			for (i = 0; i < 128; i++) {
				if (dlg_listbox_issel(ccd->listbox, dlg, i))
					cfg->wordness[i] = n;
			}
			dlg_refresh(ccd->listbox, dlg);
		}
    }
}

struct colour_data {
    union control *listbox, *redit, *gedit, *bedit, *button;
};

static const char *const colours[] = {
    "Ĭ��ǰ��", "Ĭ��ǰ�����֣�",
		"Ĭ�ϱ���", "Ĭ�ϱ������֣�",
		"����ı�", "�����ɫ",
		"ANSI ��", "ANSI �ڣ��֣�",
		"ANSI ��", "ANSI �죨�֣�",
		"ANSI ��", "ANSI �̣��֣�",
		"ANSI ��", "ANSI �ƣ��֣�",
		"ANSI ��", "ANSI �����֣�",
		"ANSI ��", "ANSI �ϣ��֣�",
		"ANSI ��", "ANSI �ࣨ�֣�",
		"ANSI ��", "ANSI �ף��֣�"
};

static void colour_handler(union control *ctrl, void *dlg,
						   void *data, int event)
{
    Config *cfg = (Config *)data;
    struct colour_data *cd =
		(struct colour_data *)ctrl->generic.context.p;
    int update = FALSE, r, g, b;
	
    if (event == EVENT_REFRESH) {
		if (ctrl == cd->listbox) {
			int i;
			dlg_update_start(ctrl, dlg);
			dlg_listbox_clear(ctrl, dlg);
			for (i = 0; i < lenof(colours); i++)
				dlg_listbox_add(ctrl, dlg, colours[i]);
			dlg_update_done(ctrl, dlg);
			dlg_editbox_set(cd->redit, dlg, "");
			dlg_editbox_set(cd->gedit, dlg, "");
			dlg_editbox_set(cd->bedit, dlg, "");
		}
    } else if (event == EVENT_SELCHANGE) {
		if (ctrl == cd->listbox) {
			/* The user has selected a colour. Update the RGB text. */
			int i = dlg_listbox_index(ctrl, dlg);
			if (i < 0) {
				dlg_beep(dlg);
				return;
			}
			r = cfg->colours[i][0];
			g = cfg->colours[i][1];
			b = cfg->colours[i][2];
			update = TRUE;
		}
    } else if (event == EVENT_VALCHANGE) {
		if (ctrl == cd->redit || ctrl == cd->gedit || ctrl == cd->bedit) {
			/* The user has changed the colour using the edit boxes. */
			char buf[80];
			int i, cval;
			
			dlg_editbox_get(ctrl, dlg, buf, lenof(buf));
			cval = atoi(buf) & 255;
			
			i = dlg_listbox_index(cd->listbox, dlg);
			if (i >= 0) {
				if (ctrl == cd->redit)
					cfg->colours[i][0] = cval;
				else if (ctrl == cd->gedit)
					cfg->colours[i][1] = cval;
				else if (ctrl == cd->bedit)
					cfg->colours[i][2] = cval;
			}
		}
    } else if (event == EVENT_ACTION) {
		if (ctrl == cd->button) {
			int i = dlg_listbox_index(cd->listbox, dlg);
			if (i < 0) {
				dlg_beep(dlg);
				return;
			}
			/*
			* Start a colour selector, which will send us an
			* EVENT_CALLBACK when it's finished and allow us to
			* pick up the results.
			*/
			dlg_coloursel_start(ctrl, dlg,
				cfg->colours[i][0],
				cfg->colours[i][1],
				cfg->colours[i][2]);
		}
    } else if (event == EVENT_CALLBACK) {
		if (ctrl == cd->button) {
			int i = dlg_listbox_index(cd->listbox, dlg);
			/*
			* Collect the results of the colour selector. Will
			* return nonzero on success, or zero if the colour
			* selector did nothing (user hit Cancel, for example).
			*/
			if (dlg_coloursel_results(ctrl, dlg, &r, &g, &b)) {
				cfg->colours[i][0] = r;
				cfg->colours[i][1] = g;
				cfg->colours[i][2] = b;
				update = TRUE;
			}
		}
    }
	
    if (update) {
		char buf[40];
		sprintf(buf, "%d", r); dlg_editbox_set(cd->redit, dlg, buf);
		sprintf(buf, "%d", g); dlg_editbox_set(cd->gedit, dlg, buf);
		sprintf(buf, "%d", b); dlg_editbox_set(cd->bedit, dlg, buf);
    }
}

struct environ_data {
    union control *varbox, *valbox, *addbutton, *rembutton, *listbox;
};

static void environ_handler(union control *ctrl, void *dlg,
							void *data, int event)
{
    Config *cfg = (Config *)data;
    struct environ_data *ed =
		(struct environ_data *)ctrl->generic.context.p;
	
    if (event == EVENT_REFRESH) {
		if (ctrl == ed->listbox) {
			char *p = cfg->environmt;
			dlg_update_start(ctrl, dlg);
			dlg_listbox_clear(ctrl, dlg);
			while (*p) {
				dlg_listbox_add(ctrl, dlg, p);
				p += strlen(p) + 1;
			}
			dlg_update_done(ctrl, dlg);
		}
    } else if (event == EVENT_ACTION) {
		if (ctrl == ed->addbutton) {
			char str[sizeof(cfg->environmt)];
			char *p;
			dlg_editbox_get(ed->varbox, dlg, str, sizeof(str)-1);
			if (!*str) {
				dlg_beep(dlg);
				return;
			}
			p = str + strlen(str);
			*p++ = '\t';
			dlg_editbox_get(ed->valbox, dlg, p, sizeof(str)-1 - (p - str));
			if (!*p) {
				dlg_beep(dlg);
				return;
			}
			p = cfg->environmt;
			while (*p) {
				while (*p)
					p++;
				p++;
			}
			if ((p - cfg->environmt) + strlen(str) + 2 <
				sizeof(cfg->environmt)) {
				strcpy(p, str);
				p[strlen(str) + 1] = '\0';
				dlg_listbox_add(ed->listbox, dlg, str);
				dlg_editbox_set(ed->varbox, dlg, "");
				dlg_editbox_set(ed->valbox, dlg, "");
			} else {
				dlg_error_msg(dlg, "Environment too big");
			}
		} else if (ctrl == ed->rembutton) {
			int i = dlg_listbox_index(ed->listbox, dlg);
			if (i < 0) {
				dlg_beep(dlg);
			} else {
				char *p, *q;
				
				dlg_listbox_del(ed->listbox, dlg, i);
				p = cfg->environmt;
				while (i > 0) {
					if (!*p)
						goto disaster;
					while (*p)
						p++;
					p++;
					i--;
				}
				q = p;
				if (!*p)
					goto disaster;
				while (*p)
					p++;
				p++;
				while (*p) {
					while (*p)
						*q++ = *p++;
					*q++ = *p++;
				}
				*q = '\0';
disaster:;
			}
		}
    }
}

struct portfwd_data {
    union control *addbutton, *rembutton, *listbox;
    union control *sourcebox, *destbox, *direction;
#ifndef NO_IPV6
    union control *addressfamily;
#endif
};

static void portfwd_handler(union control *ctrl, void *dlg,
							void *data, int event)
{
    Config *cfg = (Config *)data;
    struct portfwd_data *pfd =
		(struct portfwd_data *)ctrl->generic.context.p;
	
    if (event == EVENT_REFRESH) {
		if (ctrl == pfd->listbox) {
			char *p = cfg->portfwd;
			dlg_update_start(ctrl, dlg);
			dlg_listbox_clear(ctrl, dlg);
			while (*p) {
				dlg_listbox_add(ctrl, dlg, p);
				p += strlen(p) + 1;
			}
			dlg_update_done(ctrl, dlg);
		} else if (ctrl == pfd->direction) {
		/*
		* Default is Local.
			*/
			dlg_radiobutton_set(ctrl, dlg, 0);
#ifndef NO_IPV6
		} else if (ctrl == pfd->addressfamily) {
			dlg_radiobutton_set(ctrl, dlg, 0);
#endif
		}
    } else if (event == EVENT_ACTION) {
		if (ctrl == pfd->addbutton) {
			char str[sizeof(cfg->portfwd)];
			char *p;
			int i, type;
			int whichbutton;
			
			i = 0;
#ifndef NO_IPV6
			whichbutton = dlg_radiobutton_get(pfd->addressfamily, dlg);
			if (whichbutton == 1)
				str[i++] = '4';
			else if (whichbutton == 2)
				str[i++] = '6';
#endif
			
			whichbutton = dlg_radiobutton_get(pfd->direction, dlg);
			if (whichbutton == 0)
				type = 'L';
			else if (whichbutton == 1)
				type = 'R';
			else
				type = 'D';
			str[i++] = type;
			
			dlg_editbox_get(pfd->sourcebox, dlg, str+i, sizeof(str) - i);
			if (!str[i]) {
				dlg_error_msg(dlg, "You need to specify a source port number");
				return;
			}
			p = str + strlen(str);
			if (type != 'D') {
				*p++ = '\t';
				dlg_editbox_get(pfd->destbox, dlg, p,
					sizeof(str) - (p - str));
				if (!*p || !strchr(p, ':')) {
					dlg_error_msg(dlg,
						"You need to specify a destination address\n"
						"in the form \"host.name:port\"");
					return;
				}
			} else
				*p = '\0';
			p = cfg->portfwd;
			while (*p) {
				while (*p)
					p++;
				p++;
			}
			if ((p - cfg->portfwd) + strlen(str) + 2 <=
				sizeof(cfg->portfwd)) {
				strcpy(p, str);
				p[strlen(str) + 1] = '\0';
				dlg_listbox_add(pfd->listbox, dlg, str);
				dlg_editbox_set(pfd->sourcebox, dlg, "");
				dlg_editbox_set(pfd->destbox, dlg, "");
			} else {
				dlg_error_msg(dlg, "Too many forwardings");
			}
		} else if (ctrl == pfd->rembutton) {
			int i = dlg_listbox_index(pfd->listbox, dlg);
			if (i < 0)
				dlg_beep(dlg);
			else {
				char *p, *q;
				
				dlg_listbox_del(pfd->listbox, dlg, i);
				p = cfg->portfwd;
				while (i > 0) {
					if (!*p)
						goto disaster2;
					while (*p)
						p++;
					p++;
					i--;
				}
				q = p;
				if (!*p)
					goto disaster2;
				while (*p)
					p++;
				p++;
				while (*p) {
					while (*p)
						*q++ = *p++;
					*q++ = *p++;
				}
				*q = '\0';
disaster2:;
			}
		}
    }
}

void setup_config_box(struct controlbox *b, struct sesslist *sesslist,
					  int midsession, int protocol, int protcfginfo)
{
    struct controlset *s;
    struct sessionsaver_data *ssd;
    //struct charclass_data *ccd;
    //struct colour_data *cd;
    //struct environ_data *ed;
    //struct portfwd_data *pfd;
    union control *c;
    char *str;
	
    ssd = (struct sessionsaver_data *)
		ctrl_alloc(b, sizeof(struct sessionsaver_data));
    memset(ssd, 0, sizeof(*ssd));
    ssd->midsession = midsession;
	
    /*
	* The standard panel that appears at the bottom of all panels:
	* Open, Cancel, Apply etc.
	*/
    s = ctrl_getset(b, "", "", "");
    ctrl_columns(s, 5, 20, 20, 20, 20, 20);
    ssd->okbutton = ctrl_pushbutton(s,
				    (midsession ? "Ӧ��" : "��(O)"),
					(char)(midsession ? 'a' : 'o'),
					HELPCTX(no_help),
					sessionsaver_handler, P(ssd));
    ssd->okbutton->button.isdefault = TRUE;
    ssd->okbutton->generic.column = 3;
    ssd->cancelbutton = ctrl_pushbutton(s, "ȡ��(C)", 'c', HELPCTX(no_help),
		sessionsaver_handler, P(ssd));
    ssd->cancelbutton->button.iscancel = TRUE;
    ssd->cancelbutton->generic.column = 4;
    /* We carefully don't close the 5-column part, so that platform-
	* specific add-ons can put extra buttons alongside Open and Cancel. */
	
    /*
	* The Session panel.
	*/
    str = dupprintf("%s �Ự��������", appname);
    ctrl_settitle(b, "�Ự", str);
    sfree(str);
	
    if (!midsession) {
		s = ctrl_getset(b, "�Ự", "hostport",
			"ָ��Ҫ���ӵ��������ƻ� IP ��ַ");
		ctrl_columns(s, 2, 75, 25);
		c = ctrl_editbox(s, "��������(�� IP ��ַ)(N)", 'n', 100,
			HELPCTX(session_hostname),
			dlg_stdeditbox_handler, I(offsetof(Config,host)),
			I(sizeof(((Config *)0)->host)));
		c->generic.column = 0;
		c = ctrl_editbox(s, "�˿�(P)", 'p', 100, HELPCTX(session_hostname),
			dlg_stdeditbox_handler,
			I(offsetof(Config,port)), I(-1));
		c->generic.column = 1;
		ctrl_columns(s, 1, 100);
		/*if (backends[3].name == NULL) {
		ctrl_radiobuttons(s, "Э�飺", NO_SHORTCUT, 3,
		HELPCTX(session_hostname),
		protocolbuttons_handler, P(c),
		"Raw", 'r', I(PROT_RAW),
		"Telnet", 't', I(PROT_TELNET),
		"Rlogin", 'i', I(PROT_RLOGIN),
		NULL);
		} else {
		ctrl_radiobuttons(s, "Э�飺", NO_SHORTCUT, 4,
		HELPCTX(session_hostname),
		protocolbuttons_handler, P(c),
		"Raw", 'r', I(PROT_RAW),
		"Telnet", 't', I(PROT_TELNET),
		"Rlogin", 'i', I(PROT_RLOGIN),
		"SSH", 's', I(PROT_SSH),
		NULL);
	}*/
    }
	
    /*
	* The Load/Save panel is available even in mid-session.
	*/
    s = ctrl_getset(b, "�Ự", "savedsessions",
		midsession ? "���浱ǰ�Ự����" :
	"���롢�����ɾ���Ѵ��ڵĻỰ");
    ctrl_columns(s, 2, 75, 25);
    ssd->sesslist = sesslist;
    ssd->editbox = ctrl_editbox(s, "����ĻỰ(E)", 'e', 100,
		HELPCTX(session_saved),
		sessionsaver_handler, P(ssd), P(NULL));
    ssd->editbox->generic.column = 0;
    /* Reset columns so that the buttons are alongside the list, rather
	* than alongside that edit box. */
    ctrl_columns(s, 1, 100);
    ctrl_columns(s, 2, 75, 25);
    ssd->listbox = ctrl_listbox(s, NULL, NO_SHORTCUT,
		HELPCTX(session_saved),
		sessionsaver_handler, P(ssd));
    ssd->listbox->generic.column = 0;
    ssd->listbox->listbox.height = 7;
    if (!midsession) {
		ssd->loadbutton = ctrl_pushbutton(s, "����(L)", 'l',
			HELPCTX(session_saved),
			sessionsaver_handler, P(ssd));
		ssd->loadbutton->generic.column = 1;
    } else {
	/* We can't offer the Load button mid-session, as it would allow the
	* user to load and subsequently save settings they can't see. (And
	* also change otherwise immutable settings underfoot; that probably
		* shouldn't be a problem, but.) */
		ssd->loadbutton = NULL;
    }
    /* "Save" button is permitted mid-session. */
    ssd->savebutton = ctrl_pushbutton(s, "����(S)", 'v',
		HELPCTX(session_saved),
		sessionsaver_handler, P(ssd));
    ssd->savebutton->generic.column = 1;
    if (!midsession) {
		ssd->delbutton = ctrl_pushbutton(s, "ɾ��(D)", 'd',
			HELPCTX(session_saved),
			sessionsaver_handler, P(ssd));
		ssd->delbutton->generic.column = 1;
    } else {
		/* Disable the Delete button mid-session too, for UI consistency. */
		ssd->delbutton = NULL;
    }
    ctrl_columns(s, 1, 100);
	
    s = ctrl_getset(b, "�Ự", "otheropts", NULL);
    c = ctrl_radiobuttons(s, "�˳�ʱ�رմ���(W)��", 'w', 4,
		HELPCTX(session_coe),
		dlg_stdradiobutton_handler,
		I(offsetof(Config, close_on_exit)),
		"����", I(FORCE_ON),
		"�Ӳ�", I(FORCE_OFF),
		"�������˳�", I(AUTO), NULL);
	
		/*
		* The Session/Logging panel.
	*/
#ifdef _DEBUG
    ctrl_settitle(b, "�Ự/��־��¼", "�Ự��־��¼ѡ��");
	
    s = ctrl_getset(b, "�Ự/��־��¼", "main", NULL);
    /*
	* The logging buttons change depending on whether SSH packet
	* logging can sensibly be available.
	*/
    {
		char *sshlogname;
		if ((midsession && protocol == PROT_SSH) ||
			(!midsession && backends[3].name != NULL))
			sshlogname = "��¼ SSH ������";
		else
			sshlogname = NULL;	       /* this will disable the button */
		ctrl_radiobuttons(s, "�Ự��־��¼��", NO_SHORTCUT, 1,
			HELPCTX(logging_main),
			loggingbuttons_handler,
			I(offsetof(Config, logtype)),
			"��ȫ�ر���־��¼(T)", 't', I(LGTYP_NONE),
			"ֻ��¼�ɴ�ӡ�����(P)", 'p', I(LGTYP_ASCII),
			"��¼���лỰ���(L)", 'l', I(LGTYP_DEBUG),
			sshlogname, 's', I(LGTYP_PACKETS),
			NULL);
    }
    ctrl_filesel(s, "��־�ļ���(F)��", 'f',
		NULL, TRUE, "ѡ��Ự����־�ļ���",
		HELPCTX(logging_filename),
		dlg_stdfilesel_handler, I(offsetof(Config, logfilename)));
    ctrl_text(s, "(��־�ļ������԰��� &Y &M &D ��ʾ�����գ�"
		"&T ��ʾʱ�䣬&H ��ʾ��������)",
		HELPCTX(logging_filename));
    ctrl_radiobuttons(s, "Ҫ��¼����־�ļ��Ѵ���ʱ(E)��", 'e', 1,
		      HELPCTX(logging_exists),
			  dlg_stdradiobutton_handler, I(offsetof(Config,logxfovr)),
			  "���Ǹ���", I(LGXF_OVR),
			  "������ӵ�ĩβ", I(LGXF_APN),
			  "ÿ��ѯ��", I(LGXF_ASK), NULL);
    ctrl_checkbox(s, "����ˢ�»��浽��־�ļ�(U)", 'u',
		HELPCTX(logging_flush),
		dlg_stdcheckbox_handler, I(offsetof(Config,logflush)));
	
    if ((midsession && protocol == PROT_SSH) ||
		(!midsession && backends[3].name != NULL)) {
		s = ctrl_getset(b, "�Ự/��־��¼", "ssh",
			"ָ�� SSH ����־��¼����");
		ctrl_checkbox(s, "������֪��������(K)", 'k',
			HELPCTX(logging_ssh_omit_password),
			dlg_stdcheckbox_handler, I(offsetof(Config,logomitpass)));
		ctrl_checkbox(s, "���ԻỰ����(D)", 'd',
			HELPCTX(logging_ssh_omit_data),
			dlg_stdcheckbox_handler, I(offsetof(Config,logomitdata)));
    }
#endif
	
    str = dupprintf("%s ��������", appname);
    ctrl_settitle(b, "����", str);
    sfree(str);
	
    s = ctrl_getset(b, "����", "size", "���ô��ڴ�С");
    ctrl_columns(s, 2, 50, 50);
    c = ctrl_editbox(s, "��(R)", 'r', 100,
		HELPCTX(window_size),
		dlg_stdeditbox_handler, I(offsetof(Config,height)),I(-1));
    c->generic.column = 0;
    c = ctrl_editbox(s, "��(M)", 'm', 100,
		HELPCTX(window_size),
		dlg_stdeditbox_handler, I(offsetof(Config,width)), I(-1));
    c->generic.column = 1;
    ctrl_columns(s, 1, 100);
	
    s = ctrl_getset(b, "����", "scrollback",
		"���ô��ڻع�");
    ctrl_editbox(s, "�ع�����(S)", 's', 50,
		HELPCTX(window_scrollback),
		dlg_stdeditbox_handler, I(offsetof(Config,savelines)), I(-1));
    ctrl_checkbox(s, "��ʾ������(D)", 'd',
		HELPCTX(window_scrollback),
		dlg_stdcheckbox_handler, I(offsetof(Config,scrollbar)));
    ctrl_checkbox(s, "����ʱ���ûع�(K)", 'k',
		HELPCTX(window_scrollback),
		dlg_stdcheckbox_handler, I(offsetof(Config,scroll_on_key)));
    ctrl_checkbox(s, "ˢ����ʾʱ���ûع�(P)", 'p',
		HELPCTX(window_scrollback),
		dlg_stdcheckbox_handler, I(offsetof(Config,scroll_on_disp)));
    ctrl_checkbox(s, "��������ı�ѹ��ع�(E)", 'e',
		HELPCTX(window_erased),
		dlg_stdcheckbox_handler,
		I(offsetof(Config,erase_to_scrollback)));
	
	/*
	 * The Connection/SSH panel.
	 */
	ctrl_settitle(b, "SSH",
		      "SSH ��������");
	
	if (midsession && protcfginfo == 1) {
		s = ctrl_getset(b, "SSH", "disclaimer", NULL);
		ctrl_text(s, "Nothing on this panel may be reconfigured in mid-"
			"session; it is only here so that sub-panels of it can "
			"exist without looking strange.", HELPCTX(no_help));
	}
	
	if (!midsession) {
		/*
		s = ctrl_getset(b, "SSH", "data",
			"���͵�������������");
		ctrl_editbox(s, "Զ������(R)��", 'r', 100,
			HELPCTX(ssh_command),
			dlg_stdeditbox_handler, I(offsetof(Config,remote_cmd)),
			I(sizeof(((Config *)0)->remote_cmd)));
		
		s = ctrl_getset(b, "SSH", "protocol", "Э��ѡ��");
		ctrl_checkbox(s, "��������ն�(P)", 'p',
			HELPCTX(ssh_nopty),
			dlg_stdcheckbox_handler,
			I(offsetof(Config,nopty)));
		ctrl_checkbox(s, "��ȫ������ Shell ������(N)", 'n',
			HELPCTX(ssh_noshell),
			dlg_stdcheckbox_handler,
			I(offsetof(Config,ssh_no_shell)));*/
	}
	
	if (!midsession || protcfginfo != 1) {
		s = ctrl_getset(b, "SSH", "protocol", "Э��ѡ��");
		
		ctrl_checkbox(s, "����ѹ��(E)", 'e',
			HELPCTX(ssh_compress),
			dlg_stdcheckbox_handler,
			I(offsetof(Config,compression)));
	}
	
	if (!midsession) {
		s = ctrl_getset(b, "SSH", "protocol", "Э��ѡ��");
		
		ctrl_radiobuttons(s, "��ѡ�� SSH Э��汾��", NO_SHORTCUT, 4,
			HELPCTX(ssh_protocol),
			dlg_stdradiobutton_handler,
			I(offsetof(Config, sshprot)),
			"ֻ�� 1(L)", 'l', I(0),
			"1", '1', I(1),
			"2", '2', I(2),
			"ֻ�� 2(Y)", 'y', I(3), NULL);
	}
	
	if (!midsession || protcfginfo != 1) {
		s = ctrl_getset(b, "SSH", "encryption", "����ѡ��");
		c = ctrl_draglist(s, "���ܷ���ѡ��˳��(S)��", 's',
			HELPCTX(ssh_ciphers),
			cipherlist_handler, P(NULL));
		/*
		c->listbox.height = 6;
		
		ctrl_checkbox(s, "���� SSH-2 ����ʹ�õ�һ DES �㷨(I)", 'i',
			HELPCTX(ssh_ciphers),
			dlg_stdcheckbox_handler,
			I(offsetof(Config,ssh2_des_cbc)));
			*/
	}
	
	/*
	* The Connection/SSH/Kex panel. (Owing to repeat key
	* exchange, this is all meaningful in mid-session _if_
	* we're using SSH-2 or haven't decided yet.)
	*/
	if (protcfginfo != 1) {
		ctrl_settitle(b, "SSH/��Կ",
			"SSH ��Կ��֤����");
		
		s = ctrl_getset(b, "SSH/��Կ", "main",
			"��Կ��֤�㷨ѡ��");
		c = ctrl_draglist(s, "�㷨ѡ��˳��(S)��", 's',
			HELPCTX(ssh_kexlist),
			kexlist_handler, P(NULL));
		c->listbox.height = 5;
		
		s = ctrl_getset(b, "SSH/��Կ", "repeat",
			"��Կ�ٴ���֤����");
		
		ctrl_editbox(s, "������֤�ʱ��(���ӣ�0 ������)(T)��", 't', 20,
			HELPCTX(ssh_kex_repeat),
			dlg_stdeditbox_handler,
			I(offsetof(Config,ssh_rekey_time)),
			I(-1));
		ctrl_editbox(s, "������֤���������(0 Ϊ������)(X)��", 'x', 20,
			HELPCTX(ssh_kex_repeat),
			dlg_stdeditbox_handler,
			I(offsetof(Config,ssh_rekey_data)),
			I(16));
		ctrl_text(s, "(ʹ�� 1M ��ʾ 1 ���ֽڣ�1G ��ʾ 1 ���ֽ�)",
			HELPCTX(ssh_kex_repeat));
	}
	/*
	if (!midsession) {
		
	
	* The Connection/SSH/Auth panel.
		
		ctrl_settitle(b, "SSH/��֤",
			"SSH ��֤����");
		
		s = ctrl_getset(b, "SSH/��֤", "methods",
			"��֤��ʽ");
		ctrl_checkbox(s, "���� TIS �� CryptoCard ��֤ (SSH-1) (M)", 'm',
			HELPCTX(ssh_auth_tis),
			dlg_stdcheckbox_handler,
			I(offsetof(Config,try_tis_auth)));
		ctrl_checkbox(s, "���ԡ����ܼ��̡���֤ (SSH-2) (I)",
			'i', HELPCTX(ssh_auth_ki),
			dlg_stdcheckbox_handler,
			I(offsetof(Config,try_ki_auth)));
		
		s = ctrl_getset(b, "SSH/��֤", "params",
			"��֤����");
		ctrl_checkbox(s, "�������ӳ��(F)", 'f',
			HELPCTX(ssh_auth_agentfwd),
			dlg_stdcheckbox_handler, I(offsetof(Config,agentfwd)));
		ctrl_checkbox(s, "�������� SSH-2 ���޸��û���(U)", 'u',
			HELPCTX(ssh_auth_changeuser),
			dlg_stdcheckbox_handler,
			I(offsetof(Config,change_username)));
		ctrl_filesel(s, "��֤˽Կ�ļ�(K)��", 'k',
			FILTER_KEY_FILES, FALSE, "ѡ��˽Կ�ļ�",
			HELPCTX(ssh_auth_privkey),
			dlg_stdfilesel_handler, I(offsetof(Config, keyfile)));
	}
	
	if (!midsession) {
	
	* The Connection/SSH/Bugs panel.
		
		ctrl_settitle(b, "SSH/���",
			"���� SSH ��������������");
		
		s = ctrl_getset(b, "SSH/���", "main",
			"�����֪�� SSH ����������");
		ctrl_droplist(s, "���� SSH-1 ������Ϣ(I)", 'i', 20,
			HELPCTX(ssh_bugs_ignore1),
			sshbug_handler, I(offsetof(Config,sshbug_ignore1)));
		ctrl_droplist(s, "�ܾ����� SSH-1 ����αװ(S)", 's', 20,
			HELPCTX(ssh_bugs_plainpw1),
			sshbug_handler, I(offsetof(Config,sshbug_plainpw1)));
		ctrl_droplist(s, "���� SSH-1 RSA ��֤", 'r', 20,
			HELPCTX(ssh_bugs_rsa1),
			sshbug_handler, I(offsetof(Config,sshbug_rsa1)));
		ctrl_droplist(s, "���� SSH-2 HMAC ��Կ(M)", 'm', 20,
			HELPCTX(ssh_bugs_hmac2),
			sshbug_handler, I(offsetof(Config,sshbug_hmac2)));
		ctrl_droplist(s, "���� SSH-2 ������Կ(E)", 'e', 20,
			HELPCTX(ssh_bugs_derivekey2),
			sshbug_handler, I(offsetof(Config,sshbug_derivekey2)));
		ctrl_droplist(s, "SSH-2 RSA ǩ����������(P)", 'p', 20,
			HELPCTX(ssh_bugs_rsapad2),
			sshbug_handler, I(offsetof(Config,sshbug_rsapad2)));
		ctrl_droplist(s, "���� SSH-2 PK ��֤�Ự ID(N)", 'n', 20,
			HELPCTX(ssh_bugs_pksessid2),
			sshbug_handler, I(offsetof(Config,sshbug_pksessid2)));
		ctrl_droplist(s, "�ϸ� SSH-2 ��Կ�ٴ���֤����(K)", 'k', 20,
			HELPCTX(ssh_bugs_rekey2),
			sshbug_handler, I(offsetof(Config,sshbug_rekey2)));
    }
    */
}
