// void pipe_next_cmd(t_token_lst *lst)
// {
//   t_token *current;
//   t_token *nxt_command;
//   t_token *curr_command;
//   int fd[2];

//   current = lst->head;
//   if (!current)
//     return ;
//   nxt_command = NULL;
//   curr_command = NULL;
//   while (current && !nxt_command)
//   {
//     if (current->type == COMMAND && !curr_command)
//       curr_command = current;
//     if (curr_command && current->type == COMMAND && curr_command != current)
//       nxt_command = current;
//     current = current->next;
//   }
//   if (curr_command && nxt_command && nxt_command->prev && nxt_command->prev->type == PIPE)
//   {
//     pipe(fd);
//     curr_command->fd[1] = fd[1];
//     nxt_command->fd[0] = fd[0];
//     curr_command->piped = 1;
//   }
// }